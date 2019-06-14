<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css/login.css">
    <link rel="stylesheet" href="css/icons.css">
    <title>Log in</title>
</head>
<body class="login-body">
<div class="container login-container">
    <div class="form-container">
        <span class="icon icon-size-25 close-icon icon-black icon-button close-button"></span>
        <form method="POST" action="/request.php" novalidate>
            <h2 class="title-font login-title">Найти всех специалистов</h2>
            <div class="form-label-group">
                <input type="text" class="input-form" name="spicialization" placeholder="специальность">
            </div>

            <button class="btn btn-box-3 btn-color-green" type="submit" name="submit">
                <div class="success-btn-font">Найти</div>
            </button>
            <button class="btn btn-box-3 btn-color-red" type="reset" name="reset">
                <div class="success-btn-font">Отчистить</div>
            </button>
        </form>
    </div>
</div>
</body>
</html>
