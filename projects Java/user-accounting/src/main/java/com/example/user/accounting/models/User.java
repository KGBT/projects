package com.example.user.accounting.models;

import jakarta.persistence.*;
import jakarta.validation.constraints.Size;
import lombok.Data;

import java.util.HashSet;
import java.util.Objects;
import java.util.Set;


@Data //Генерирует геттеры и сеттеры
@Entity //сущность
@Table(name = "users") //таблица
public class User { //Модель User, которая сохраняется в БД
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "username", unique = true, length = 30)
    @Size(min = 2, message = "Минимальная длина 2 символов") //ограничения
    @Size(max = 30, message = "Максимальная длина 30 символов")
    private String username;

    @Column(name = "password", length = 255)
    private String password;

    @Transient //данное поле не сохраняется в БД. Используется только для сравнения паролей при регистрации.
    private String passwordConfirm;

    @Column(name = "email", length = 30)
    @Size(min = 2, message = "Минимальная длина 2 символа")
    private String email;

    @Column(name = "name", length = 30)
    @Size(min = 2, message = "Минимальная длина 2 символа")
    private String name;

    @Column(name = "surname", length = 30)
    @Size(min = 2, message = "Минимальная длина 2 символа")
    private String surname;

    @Column(name = "role", length = 10)
    private String role;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return Objects.equals(id, user.id) && Objects.equals(username, user.username) && Objects.equals(password, user.password) && Objects.equals(passwordConfirm, user.passwordConfirm) && Objects.equals(email, user.email) && Objects.equals(name, user.name) && Objects.equals(surname, user.surname) && Objects.equals(role, user.role);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, username, password, passwordConfirm, email, name, surname, role);
    }

}
