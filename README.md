# minishell

Наша реализация bash. Это командный проект вместе с [zotochev](https://github.com/zotochev).

<p align="center">
  <img src="https://i.ibb.co/hmbKcfp/Screen-Shot-2021-05-16-at-6-29-47-PM.png" width="100%" />
</p>


### Как запустить

Команда ``make`` для создания исполняемого файла ``minishell``.

Запуск исполняемого файла

```
./minishell
```

### Возможности 

Minishell запускает исполняемые файлы из абсолюного пути или из переменной окружения PATH (`` / bin / ls `` или ``ls`` ), включая аргументы или параметры. 

`'` `и` `"` работают так же, как bash, реализовано экраннирование ``\"``, ``\'``, ``\\``, ``\|``.

Можно разделять команды с помощью ``;``, а также использовать редиректы ``> `` `` >> `` `` <`` и пайпы `` | ``.

Переменные среды обрабатываются, как ``$HOME``, включая код возврата ``$?``. Также можно создавать и удалять переменные.

Также можно использовать ``Ctrl-C`` для прерывания и ``Ctrl- \`` для выхода из программы, а также ``Ctrl-D`` для вызова EOF, как в bash.

Некоторые функции являются «встроенными», то есть мы не вызываем исполняемый файл, мы перекодировали их напрямую. Это касается ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` и ``exit``.

### Источники

* [Структура программы](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [Shellsyntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&ab_channel=CodeVault)
