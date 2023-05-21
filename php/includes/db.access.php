<?php

$serverName = "database";
$dBUsername = "root";
$dBPassword = "WkG7vqWUF65W9o!z";
$dBName = "tavoletta_grafica";

$conn = mysqli_connect($serverName, $dBUsername, $dBPassword, $dBName);

if(!$conn){
    die("Connection failed: " . mysqli_connect_error());
}