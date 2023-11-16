package com.example.user.accounting.controller;

import com.example.user.accounting.models.RoleProfil;
import com.example.user.accounting.models.User;
import com.example.user.accounting.service.UserService;
import com.example.user.accounting.service.UserValidationService;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;

import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.validation.ObjectError;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;



@Controller
@RequestMapping("/")
public class UserController {
    private final UserService userService; //логика приложения
    private final UserValidationService userValidationService; //логика проверки корректности
    private final BCryptPasswordEncoder encoder; //шифрование пароля

    @Autowired
    public UserController(UserService userService, UserValidationService userValidationService, BCryptPasswordEncoder encoder) {
        this.userService = userService;
        this.userValidationService = userValidationService;
        this.encoder = encoder;
    }

    @GetMapping
    public String login() {
        return "login";
    }


    @GetMapping("/registration")
    public String registration(User user) {
        return "registration";
    }

    @PostMapping("/registration")
    public String registrationForm(@Valid User user, BindingResult result) {
        //@Valid - Проверка данных
        //BindingResult - Из него мы можем узнать были ли ошибки валидации
        allValidation(user, result);
        if (result.hasErrors()) {

            return "registration";
        }
        user.setRole(RoleProfil.USER.getUserProfileType()); //Устанавливаем роль
        String pass = encoder.encode(user.getPassword()); //шифруем пароль
        user.setPassword(pass);
        userService.saveUser(user);
        return "redirect:/";
    }


    @GetMapping("/administration")
    public String administration(Model model) {
        model.addAttribute("users", userService.findAllUsers());
        return "administration";
    }

    @GetMapping("/userCreate")
    public String userCreate(User user) {
        return "userCreate";
    }

    @PostMapping("/userCreate")
    public String userCreateForm(@Valid User user, BindingResult result) {
        if (user.getRole() == null || user.getRole().isEmpty()){
            ObjectError error = new ObjectError("notRole", "Выберите роль");
            result.addError(error);
        }
        validationValidEmail(user, result);
        validationValidUsername(user, result);
        validationValidPassword(user, result);

        validationCreateEmail(user, result);
        validationCreateUsername(user, result);

        if (result.hasErrors()) {
            return "userCreate";
        }
        String pass = encoder.encode(user.getPassword());
        user.setPassword(pass);
        user.setRole(user.getRole());
        userService.saveUser(user);
        return "redirect:/administration";
    }

    @GetMapping("/userDelete/{id}") // - передаем id удаляемого пользователя
    public String deleteUser(@PathVariable("id") Long id) {
        User user = userService.findByUsername(getAuthUsername());

        if (id.equals(user.getId())){

            return "redirect:/administration";
        }

        userService.deleteUserById(id);
        return "redirect:/administration";
    }

    @GetMapping("/userUpdateAdmin/{id}")
    public String updateUserAdmin(@PathVariable("id") Long id, Model model) {
        User user = userService.findUserById(id);
        model.addAttribute("user", user);
        return "userUpdateAdmin";
    }

    @PostMapping("/userUpdateAdmin")
    public String updateUserAdminForm(@Valid User user, BindingResult result) {

        User userFromDB = userService.findUserById(user.getId());

        if (user.getPassword() == null || user.getPassword().isEmpty()) {
            user.setPassword(userFromDB.getPassword());
        } else {
            validationValidPassword(user, result);
            if (!result.hasGlobalErrors()) {
                user.setPassword(encoder.encode(user.getPassword()));
            }

        }

        if (!user.getEmail().equals(userFromDB.getEmail())) {
            validationCreateEmail(user, result);
        }

        validationValidEmail(user, result);

        if (result.hasErrors()) {
            return "/userUpdateAdmin";
        }

        userService.saveUser(user);
        return "redirect:/administration";
    }



    @GetMapping("/home")
    public String home(Model model) {
        User user = userService.findByUsername(getAuthUsername());
        model.addAttribute("user", userService.findByUsername(user.getUsername()));
        return "home";
    }

    @GetMapping("/page")
    public String page(Model model) {
        User userFrDB = userService.findByUsername(getAuthUsername());
        model.addAttribute("user", userFrDB);
        return "page";
    }

    @GetMapping("userUpdate/{id}")
    public String userUpdate(@PathVariable("id") Long id, Model model) {
        User user = userService.findUserById(id);
        model.addAttribute("user", user);
        return "userUpdate";
    }

    @PostMapping("userUpdate")
    public String userUpdateForm(@Valid User user, BindingResult result) {

        validationPasswords(user, result);
        if (!user.getPassword().isEmpty()) {
            validationValidPassword(user, result);
        }
        if (result.hasErrors()) {
            return "userUpdate";
        }
        User userFromDB = userService.findUserById(user.getId());
        if (!user.getPassword().isEmpty()) {
            userFromDB.setPassword(null);
            userFromDB.setPassword(encoder.encode(user.getPassword()));
        }
        userFromDB.setName(user.getName());
        userFromDB.setSurname(user.getSurname());

        userService.saveUser(userFromDB);
        return "redirect:/page";
    }

    private String getAuthUsername() { // - метод, который позволяет получить авторизированного пользователя
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        return auth.getName();
    }

    private void allValidation(@Valid User user, BindingResult result) {
        validationCreateUsername(user, result);
        validationCreateEmail(user, result);
        validationValidEmail(user, result);
        validationValidUsername(user, result);
        validationPasswords(user, result);
        validationValidPassword(user, result);
    }

    private void validationPasswords(@Valid User user, BindingResult result) {
        String message = userValidationService.isValidPasswords(user);
        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("invalidPasswords", message);
            result.addError(error);
        }
    }

    private void validationCreateUsername(@Valid User user, BindingResult result) {
        String message = userValidationService.createUserError(user);

        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("createUserError", message);
            result.addError(error);
        }
    }

    private void validationCreateEmail(@Valid User user, BindingResult result) {
        String message = userValidationService.createEmailError(user);
        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("createEmailError", message);
            result.addError(error);
        }
    }

    private void validationValidUsername(@Valid User user, BindingResult result) {
        String message = userValidationService.isValidUsername(user);

        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("invalidUsername", message);
            result.addError(error);
        }


    }

    private void validationValidEmail(@Valid User user, BindingResult result) {
        String message = userValidationService.isSimpleValidEmail(user);
        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("invalidEmail", message);
            result.addError(error);
        }
    }

    private void validationValidPassword(@Valid User user, BindingResult result) {
        String message = userValidationService.minLengthPassword(user);
        if (!message.isEmpty()) {
            ObjectError error = new ObjectError("isEmptyPass", message);
            result.addError(error);
        }
    }
}





   /*
        String message = userValidationService.createUserError(user);

        if (!message.isEmpty()){
            ObjectError error = new ObjectError("createError", message);
            result.addError(error);
        }

        message = userValidationService.isValidUsername(user);

        if(!message.isEmpty()){
            ObjectError error = new ObjectError("invalidUsername", message);
            result.addError(error);
        }

        message = userValidationService.isValidPasswords(user);
        if (!message.isEmpty()){
            ObjectError error = new ObjectError("invalidPasswords", message);
            result.addError(error);
        }

        message = userValidationService.isSimpleValidEmail(user);
        if (!message.isEmpty()){
            ObjectError error = new ObjectError("invalidEmail", message);
            result.addError(error);
        }*/
