# minishell

Наш собственный маленький bash. 

<p align="center">
  <img src="https://i.imgur.com/En13A7p.png" width="100%" />
</p>


### Как запустить

Используй ``make`` для создания исполняемого файла ``minishell``.

Запусти исполняемый файл

```
./minishell
```

### Возможности 

Minishell запускает исполняемые файлы из абсолютного, относительного или окружения PATH (`` / bin / ls '' или `` ls ''), включая аргументы или параметры. `'` `и` `" `работают так же, как bash, за исключением многострочных команд.

Вы можете разделять команды с помощью ``;``, а также использовать редиректы ``> `` `` >> `` `` <`` и пайпы `` | ``.

Переменные среды обрабатываются, как $ HOME, включая код возврата $?

Наконец, вы можете использовать Ctrl-C для прерывания и Ctrl- \ для выхода из программы, а также Ctrl-D для вызова EOF, как в bash.

Некоторые функции являются «встроенными», то есть мы не вызываем исполняемый файл, мы перекодировали их напрямую. Это касается echo, pwd, cd, env, export, unset и exit.

### Credit

This two-person project was done with [macrespo](https://github.com/macrespo42).

I was responsible for the parsing, argument checking, execution, redirection and piping.

Macrespo took care of the environment variables, built-in functions, and signal handling.
