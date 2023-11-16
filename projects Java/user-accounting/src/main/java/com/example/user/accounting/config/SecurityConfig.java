
package com.example.user.accounting.config;

import com.example.user.accounting.service.UserService;
import lombok.RequiredArgsConstructor;
import org.apache.tomcat.util.net.openssl.ciphers.Authentication;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.dao.DaoAuthenticationProvider;
import org.springframework.security.config.annotation.authentication.configuration.AuthenticationConfiguration;
import org.springframework.security.config.annotation.authentication.configuration.EnableGlobalAuthentication;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configurers.AbstractHttpConfigurer;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.web.bind.annotation.PathVariable;

import java.beans.Encoder;

@EnableWebSecurity // - аннотация для включения безопасности
@RequiredArgsConstructor // - Самостоятельно создаст конструктор
@Configuration
public class SecurityConfig {

    private final UserService userService;

    @Bean
    // тут настраивается фильтр безопасности
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http.authorizeHttpRequests(auth -> auth
                        .requestMatchers("/").permitAll() // - запросы по этим путям доступны всем
                        .requestMatchers("/registration").permitAll()

                        .requestMatchers("/home").authenticated() // - запросы доступны только авторизованным пользователям
                        .requestMatchers("/page").authenticated()
                        .requestMatchers("/userUpdate").authenticated()

                        .requestMatchers("/administration").hasRole("ADMIN") // - запросы доступны только администраторам
                        .requestMatchers("/userCreate").hasRole("ADMIN")
                        .requestMatchers("/userDelete").hasRole("ADMIN")
                        .requestMatchers("/userUpdateAdmin").hasRole("ADMIN")

                        .anyRequest().permitAll()
                ).csrf(AbstractHttpConfigurer::disable) // - отключаем защиту csrf
                .formLogin(form -> form // - настраиваем собственную страницу с авторизацией и регистрацией(по умолчанию регистрации нет)
                        .loginPage("/")
                        .loginProcessingUrl("/")
                        .failureUrl("/logout")
                        .defaultSuccessUrl("/home")
                )
                .logout(logout -> logout // - настраиваем выход с "аккаунта", очищаем сессии, куки
                        .logoutUrl("/logout")
                        .invalidateHttpSession(true)
                        .clearAuthentication(true)
                        .deleteCookies("JSESSIONID")
                        .logoutSuccessUrl("/")
                )
        ;

        return http.build();
    }

    @Bean
    //Используется для аутентификации имени пользователя и пароля.
    //https://docs.spring.io/spring-security/reference/servlet/authentication/passwords/dao-authentication-provider.html
    public DaoAuthenticationProvider authenticationProvider() {
        DaoAuthenticationProvider daoAuthenticationProvider = new DaoAuthenticationProvider();
        daoAuthenticationProvider.setPasswordEncoder(passwordEncoder());
        daoAuthenticationProvider.setUserDetailsService(userService);
        return daoAuthenticationProvider;
    }

    @Bean
    // Предоставляем спрингу объект для шифрования пароля
    public BCryptPasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    /*
    @Bean

    public AuthenticationManager authenticationManager(AuthenticationConfiguration authenticationConfiguration) throws Exception {
        return authenticationConfiguration.getAuthenticationManager();
    }
     */
}
