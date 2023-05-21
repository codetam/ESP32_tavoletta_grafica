<?php include_once "additional_pages/header.php"; ?>

<section class="form-login">
<h2>Login</h2>
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

    <?php
    if(isset($_GET["error"])){
        if($_GET["error"]=="empty_fields"){
            echo "<p>Non sono stati compilati tutti i campi!</p>";
        }
        else if($_GET["error"]=="invalid_credentials"){
            echo "<p>Credenziali errate!</p>";
        }
    }
    ?>
</section>

<?php include_once "additional_pages/footer.php"; ?>