<?php include_once "additional_pages/header.php"; ?>

<section class="form-login">
<h1>Login</h1>
<?php
    /* In base alla GET ritornata vengono date indicazioni all'utente */
    if(isset($_GET["error"])){
        if($_GET["error"]=="empty_fields"){
            echo "<h3>Non sono stati compilati tutti i campi!</h3>";
        }
        else if($_GET["error"]=="invalid_credentials"){
            echo "<h3>Credenziali errate!</h3>";
        }
    }
?>
    <form action="includes/check_login.php" method="post">
        <div class="form-group">
            <label for="uid">Username</label>
            <input type="text" id="uid" name="uid" placeholder="Username" required>
        </div>
        <div class="form-group">
            <label for="pwd">Password</label>
            <input type="password" id="pwd" name="pwd" placeholder="Password" required>
        </div>
        <button type="submit" name="submit">Accedi</button>
    </form>

    
</section>

<?php include_once "additional_pages/footer.php"; ?>