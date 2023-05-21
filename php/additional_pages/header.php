<?php
session_start();
?>

<html lang="en" dir="ltr">

<head>
    <meta charset="utf-8">
    <title>Tavoletta grafica</title>
    <link rel='stylesheet' href='https://fonts.googleapis.com/css?family=DM Sans'>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
    <link rel="stylesheet" href="../css/style.css">
    <link rel="stylesheet" href="../css/forms.css">
    <link rel="stylesheet" href="../css/nav.css">
    <link rel="stylesheet" href="../css/images.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script type="text/javascript" src="../js/script.js"></script>
</head>
<body>
<nav>
    <div class="wrapper">
        <ul>
            <li class="top-buttons">
                <img src="/additional_pages/logo.png" alt="logo">
                <br>
                <a class ="explore-button" href=/explore.php>Esplora</a>
            <?php
            if(isset($_SESSION["uid"])){
?>
                <a href=/profile.php>Profilo</a>
            </li>
            <li class="bottom-buttons">
                <li><a href=/includes/check_logout.php>Log out</a></li>
            </li>
<?php 
            }
            else {
?>
            </li>
            <li class="bottom-buttons">
                <a href="/login.php">Login</a>
                <a href="/signup.php">Registrati</a>
            </li>
<?php
            };
            ?>
        </ul>
    </div>
</nav>