<?php include_once "additional_pages/header.php"; ?>

<section class="form-registrazione">
    <h1>Registrazione</h1>
    <?php
    /* In base alla GET ritornata vengono date indicazioni all'utente */
    if(isset($_GET["error"])){
        switch($_GET["error"]){
            case "empty_fields":
                echo "<h3>Non sono stati compilati tutti i campi!</h3>";
                break;
            case "pwd_not_matching":
                echo "<h3>Le password inserite non combaciano!</h3>";
                break;
            case "invalid_username":
                echo "<h3>Username non valido!</h3>";
                break;
            case "existing_username":
                echo "<h3>Username già registrato!</h3>";
                break;
            case "system_error":
                echo "<h3>Errore del sistema!</h3>";
                break;
            case "none":
                echo "<h2>Utente registrato con successo!</h2>";
                break;
        }
    }
?>
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
        <button type="submit" name="submit">Registrati</button>
    </form>

</section>    

<?php include_once "additional_pages/footer.php"; ?>