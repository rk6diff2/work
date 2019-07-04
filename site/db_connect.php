<?php
try{
    $pdo=new PDO ('mysql:host=Localhost;dbname=miles_program', 'root','root');
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); // АТРИБУТУ, УПРАВЛЯЮЩЕМУ ВЫВОДОМ ОШИБОК, ЗАДАЕТСЯ РЕЖИМ ВЫБРОСА ИСКЛЮЧЕНИЙ
    $pdo->exec('SET NAMES "utf8"');
} catch (PDOException $e) {
    $output = 'Невозможно подключиться к серверу БД '. $e->getMessage();
    echo $output."<br>";
    exit();
}
