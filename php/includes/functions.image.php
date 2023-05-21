<?php

function drawImage($image_string) {
    $x = 120;
    $y = 80;

    $gd = imagecreatetruecolor($x, $y);
    $char_array = str_split($image_string);

    $black = imagecolorallocate($gd, 0, 0, 0);
    $white = imagecolorallocate($gd, 255, 255, 255);
    $lightgrey = imagecolorallocate($gd, 211, 211, 211);
    $blue = imagecolorallocate($gd, 0, 0, 255);
    $green = imagecolorallocate($gd, 0, 255, 0);
    $red = imagecolorallocate($gd, 255, 0, 0);
    $yellow = imagecolorallocate($gd, 255, 255, 0);
    $orange = imagecolorallocate($gd, 255, 165, 0);

    $k = 0;

    for ($i = 0; $i < 120; $i++) {
        for ($j = 0; $j < 80; $j++) {
            switch ($char_array[$k]) {
                case "0":
                    imagesetpixel($gd, $i, $j, $black);
                    break;
                case "1":
                    imagesetpixel($gd, $i, $j, $white);
                    break;
                case "L":
                    imagesetpixel($gd, $i, $j, $lightgrey);
                    break;
                case "B":
                    imagesetpixel($gd, $i, $j, $blue);
                    break;
                case "G":
                    imagesetpixel($gd, $i, $j, $green);
                    break;
                case "R":
                    imagesetpixel($gd, $i, $j, $red);
                    break;
                case "Y":
                    imagesetpixel($gd, $i, $j, $yellow);
                    break;
                case "O":
                    imagesetpixel($gd, $i, $j, $orange);
                    break;
            }
            $k++;
        }
    }
    return $gd;
}
//ritorna un array di stringhe dove ogni stringa corrisponde ad un'immagine
function getUserImages($conn, $userId){
    $sql = "SELECT * FROM images WHERE userId = " . $userId . ";";
    $result = mysqli_query($conn, $sql);
    $imageList = array();
    while($image = mysqli_fetch_assoc($result)){
        array_push($imageList, $image);
    }
    return $imageList;
}

function getAllImages($conn){
    $sql = "SELECT * FROM images;";
    $result = mysqli_query($conn, $sql);
    $imageList = array();
    while($image = mysqli_fetch_assoc($result)){
        array_push($imageList, $image);
    }
    shuffle($imageList);
    return $imageList;
}