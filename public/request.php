<?php
// Подключение к базе данных
include_once('./db_connect.php');
$category = $_POST['category'];
$sql= 'SELECT * FROM catalog JOIN product p ON (item_id = p.id) WHERE category = ?;';
try{
    $sqlStatement = $pdo->prepare($sql);
    echo $category;
    $result= $sqlStatement->execute([$category]);
    foreach ($sqlStatement as $row) {
        echo $row['name'] .' '. $row['item_cost'] .' '. $row['material'] .' '.$row['unit'] .
            ' '.$row['enter_date'] .' '.$row['num_in_stock'].
            ' '.$row['num_fix_date'] .' '.$row['num_in_res'] .' '.'\n';
        //  id | item_id | item_cost | enter_date          | num_fix_date        | num_in_stock | res_fix_date        | num_in_res | id | code      | category | name  | material | unit
    }
} catch (PDOException $e) {
    $output = 'Ошибка при извлечении данных  '. $e->getMessage();
    echo $output."<br>";
    exit();
}
