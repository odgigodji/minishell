# minishell

Наша реализация bash. Это командный проект вместе с [zotochev](https://github.com/zotochev).

<p align="center">
  <img src="https://i.ibb.co/hmbKcfp/Screen-Shot-2021-05-16-at-6-29-47-PM.png" width="100%" />
</p>


### Как запустить

Команда ``make`` для создания исполняемого файла ``minishell``.

Запусти исполняемый файл

```
./minishell
```

### Возможности 

Minishell запускает исполняемые файлы из абсолюного пути или из переменной окружения PATH (`` / bin / ls `` или ``ls`` ), включая аргументы или параметры. `'` `и` `"` работают так же, как bash, за исключением многострочных команд.

Можно разделять команды с помощью ``;``, а также использовать редиректы ``> `` `` >> `` `` <`` и пайпы `` | ``.

Переменные среды обрабатываются, как $HOME, включая код возврата $?

Также можно использовать Ctrl-C для прерывания и Ctrl- \ для выхода из программы, а также Ctrl-D для вызова EOF, как в bash.

Некоторые функции являются «встроенными», то есть мы не вызываем исполняемый файл, мы перекодировали их напрямую. Это касается echo, pwd, cd, env, export, unset и exit.

