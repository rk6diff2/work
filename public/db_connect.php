<?php
try {
    $pdo = new PDO ('mysql:host=Localhost;dbname=stock', 'stock', 'admin');
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); // АТРИБУТУ, УПРАВЛЯЮЩЕМУ ВЫВОДОМ ОШИБОК, ЗАДАЕТСЯ РЕЖИМ ВЫБРОСА ИСКЛЮЧЕНИЙ
    $pdo->exec('SET NAMES "utf8"');
} catch (PDOException $e) {
    $output = 'Невозможно подключиться к серверу БД   ' . $e->getMessage();
    echo $output . "<br>";
    exit();
}
