<?php include_once "additional_pages/header.php"; ?>

<section class="form-registrazione">
    <h2>Registrazione</h2>
    <form action="includes/check_signup.php" method="post">
        <div class="form-group">
            <label for="uid">Username</label>
            <input type="text" id="uid" name="uid" placeholder="Username" required>
        </div>
        <div class="form-group">
            <label for="pwd">Password</label>
            <input type="password" id="pwd" name="pwd" placeholder="Password" required>
        </div>
        <div class="form-group">
            <label for="pwdrepeat">Conferma password</label>
            <input type="password" id="pwdrepeat" name="pwdrepeat" placeholder="Conferma password" required>
        </div>
        <button type="submit" name="submit">Conferma</button>
    </form>

    <?php
    if(isset($_GET["error"])){
        switch($_GET["error"]){
            case "empty_fields":
                echo "<p>Non sono stati compilati tutti i campi!</p>";
                break;
            case "pwd_not_matching":
                echo "<p>Le password inserite non combaciano!</p>";
                break;
            case "invalid_username":
                echo "<p>Username non valido!</p>";
                break;
            case "existing_username":
                echo "<p>Username già registrato!</p>";
                break;
            case "system_error":
                echo "<p>Errore del sistema!</p>";
                break;
            case "none":
                echo "<p>Utente registrato con successo!</p>";
                break;
        }
    }
?>

</section>    

<?php include_once "additional_pages/footer.php"; ?>