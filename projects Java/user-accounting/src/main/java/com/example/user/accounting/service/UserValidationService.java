package com.example.user.accounting.service;

import com.example.user.accounting.models.User;
import com.example.user.accounting.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

@Service
//Класс используется для проверки корректности введенных данных
public class UserValidationService {
    private final UserRepository userRepository;
    @Autowired
    public UserValidationService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public String createUserError(User user){
        String message = "";
        if (userRepository.existsByUsername(user.getUsername())){
            message = "Пользователь с таким именем существует.";
        }
        return message;
    }
    public String createEmailError(User user){
        String message = "";
        if (userRepository.existsByEmail(user.getEmail())) {
            message = "Пользователь с таким Email уже зарегистрирован.";
        }
        return message;
    }
    public String isValidUsername(User user){
        String regex = "^[a-zA-Z][a-zA-Z0-9-_\\.]{1,20}$";
        String message = "";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(user.getUsername());
        if (!matcher.matches()){
            message = "Некорректный логин.";
        }
        return message;
    }

    public String isValidPasswords(User user){
        String message = "";
        if (!user.getPassword().equals(user.getPasswordConfirm())){
            message = "Пароли не совпадают.";
        }
        return message;
    }

    public String minLengthPassword(User user){
        String message="";
        if (user.getPassword().length() < 4){
            message = "Минимальная длина пароля 4 символа";
        }
        return message;
    }

    public String isSimpleValidEmail(User user){
        String regex = "^(.+)@(\\S+)$";
        String message="";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(user.getEmail());
        if (!matcher.matches()){
            message = "Некорректный Email.";
        }
        return message;

    }



}
