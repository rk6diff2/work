<?php
// Подключение к базе данных
include_once('./db_connect.php');
$year = $_GET['year'];
$month = $_GET['months'];

$sql = 'SELECT  d.uid, profile_id , ticket_id , price , buy_date,
       miles , flight , dep_airport ,
       arr_airport , dep_date, class FROM detail d
           JOIN ticket t ON (d.ticket_id = t.uid) WHERE YEAR(d.buy_date) = ? AND MONTH(d.buy_date) = ?;';
try {
    $sqlStatement = $pdo->prepare($sql);
    $result = $sqlStatement->execute([$year, $month]);
    foreach ($sqlStatement as $row) {
        echo $row['uid']." ".$row['profile_id']." ".$row['ticket_id']." ".
            $row['price']." ".$row['buy_date']." ".$row['miles']." ".
            $row['flight']." ".$row['dep_airport']." ".$row['arr_airport']." ".
            $row['dep_date']." ".$row['class']. "\n";
    }
} catch (PDOException $e) {
    $output = 'Ошибка при извлечении данных ' . $e->getMessage();
    echo $output . "<br>";
    exit();
}
