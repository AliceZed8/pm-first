<!doctype html>
<html lang="ru">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Yummy Chan</title>

    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Comfortaa:wght@300;400;500;600;700&display=swap" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ" crossorigin="anonymous">
    <link href="css/style.css" rel="stylesheet">
</head>
<body>
<header class="yheader container-fluid">
    <div class="container">
        <div class="row">
            <div class="col-4">
                <h1><a href="/" class = "logo">Yummy Chan</a></h1>
            </div>
            <nav class="col-6">
                <ul class="headul">
                    <li class = "menu_li"
                        onmouseenter="header_hover(this, true)"
                        onmouseleave="header_hover(this, false)"><a  href="#">Сериалы</a></li>
                    <li class = "menu_li"
                        onmouseenter="header_hover(this, true)"
                        onmouseleave="header_hover(this, false)"><a  href="#">Фильмы</a></li>
                    <li class = "menu_li"
                        onmouseenter="header_hover(this, true)"
                        onmouseleave="header_hover(this, false)"><a  href="#">Онгоинги</a></li>
                </ul>
            </nav>
            <nav class="col-2">
                <ul class="headul2">
                    <li>
                        <i class="change-theme fa-regular fa-moon" onclick="change_theme(this)"></i>
                    </li>
                    <li>
                        <span class="profile">
                            <i class="fa fa-user-circle-o" aria-hidden="true"></i>
                            <ul class="authul">
                                <li><a href="#">Вход</a></li>
                                <li><a href="#">Регистрация</a></li>
                            </ul>
                        </span>
                    </li>
                </ul>
            </nav>

        </div>
    </div>
</header>

<script src="js/ychan.js"></script>
<script src="https://kit.fontawesome.com/319d747c75.js" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ENjdO4Dr2bkBIFxQpeoTz1HIcje39Wm4jDKdf19U8gI4ddQ3GYNS7NTKfAdVQSZe" crossorigin="anonymous"></script>
</body>
</html>







