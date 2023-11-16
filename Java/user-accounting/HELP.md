# Инструкция

### Предварительная настройка окружения

Приложение использует JDK версии 18, СУБД PostgreSQL с версией >= 16.
После первого запуска приложения необходимо в базе данных PostgresQL создать пользователя с правами администратора.

**Пользователь**:
* логин: admin
* пароль: $2a$12$7npiomwsA7ivxoO1HwE6M.CD2MLk2FoWEIXZM1Lvz1QZgkNZHhHQC 
* роль:
ROLE_ADMIN

либо выполнить sql-скрипт:

```
INSERT INTO public.users(
  email, name, password, role, surname, username)
  VALUES ('admin@admin.com', 'admin', 
  '$2a$12$7npiomwsA7ivxoO1HwE6M.CD2MLk2FoWEIXZM1Lvz1QZgkNZHhHQC', 
  'ROLE_ADMIN', 'adminov', 'admin');
```

**База данных**: user_accounting_app

**Порт подключения**: 5432


### Сборка и запуск

Осуществляется при помощи сборочной системы Maven, проект можно открыть в IntelliJ Idea.

При первом запуске приложение создаёт необходимые таблицы.

Точка входа в приложение: [http://localhost:8080](http://localhost:8080)

\
Логин админа: admin
\
Пароль: admin


\
\
**Автор: Иван Никитин, 21.10.2023**

