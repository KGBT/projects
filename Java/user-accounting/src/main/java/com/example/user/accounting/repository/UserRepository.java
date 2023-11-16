package com.example.user.accounting.repository;

import com.example.user.accounting.models.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository //Репозиторий
//в дженерики вписываем модель и тип Id
public interface UserRepository extends JpaRepository<User, Long> {

    //Используется для взаимодействия с БД
    //Можно задать собственный метод без реализации. Для этого необходимо написать тип возвращаемого значения, и обязательно соблюдать наименование
    //Например:
    // тип возвращаемого значения findByПишемПолеПоКоторомуПроисходитПоиск(Параметр)
    //Ниже представлены методы, которых нет в JpaRepository
    User findByUsername(String username);

    boolean existsByUsername(String username);
    boolean existsByEmail(String email);


}
