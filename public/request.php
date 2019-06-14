<?php
// Подключение к базе данных
include_once('./db_connect.php');
$spicialization = $_POST['spicialization'];
$sql= 'SELECT Name, LastName FROM medicon m WHERE m.Specialization= ?;';
try{
    $sqlStatement = $pdo->prepare($sql);
    $result= $sqlStatement->execute([$spicialization]);
    foreach ($sqlStatement as $row) {
        echo $row['Name'] .  " " . $row['LastName'] . "\n";
    }
} catch (PDOException $e) {
    $output = 'Ошибка при извлечении данных  '. $e->getMessage();
    echo $output."<br>";
    exit();
}
