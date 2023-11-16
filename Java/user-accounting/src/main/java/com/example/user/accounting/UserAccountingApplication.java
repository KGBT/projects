package com.example.user.accounting;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication

public class UserAccountingApplication {

	public static void main(String[] args) {
		SpringApplication.run(UserAccountingApplication.class, args);
	}

}
