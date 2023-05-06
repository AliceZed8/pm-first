let cookie_theme = getCookie("theme");
let theme;

switch (cookie_theme) {
    case "day":
        theme = true;
        set_theme(cookie_theme);
        break;
    case "night":
        theme = false;
        set_theme(cookie_theme);
        break;
    default:
        theme = true;
        set_theme("day");
        document.cookie = "theme=day";
        break;
}
function getCookie(name) {
    let matches = document.cookie.match(new RegExp(
        "(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
    ));
    return matches ? decodeURIComponent(matches[1]) : undefined;
}
function set_theme(str) {
    if (str == "day") {
        document.querySelector(".yheader").style.backgroundColor = "white";
        let li_list = document.getElementsByClassName("menu_li");
        for (let i = 0; i < li_list.length; i++) {
            li_list[i].style.backgroundColor = "white";
            li_list[i].querySelector("a").style.color = "rgb(160, 82, 235)";
        }
    } else {
        document.querySelector(".yheader").style.backgroundColor = "rgb(49,49,50)";
        let li_list = document.getElementsByClassName("menu_li");
        for (let i = 0; i < li_list.length; i++) {
            li_list[i].style.backgroundColor = "rgb(49,49,50)";
            li_list[i].querySelector("a").style.color = "white";
        }
    }
}
function header_hover(e, type) {
    //type: bool (mouseenter - true, mouseleave - false)
    if (type) {
        e.style.backgroundColor = "rgb(160, 82, 235)";
        e.querySelector("a").style.color = "white";
    } else {
        if (theme) {
            e.style.backgroundColor = "white";
            e.querySelector("a").style.color = "rgb(160, 82, 235)";
        } else {
            e.style.backgroundColor = "rgb(49,49,50)";
            e.querySelector("a").style.color = "white";
        }
    }
}
function change_theme(e) {
    if (theme) {
        set_theme("night");
        document.cookie = "theme=night";
        theme = false;
    } else {
        set_theme("day");
        document.cookie = "theme=day";
        theme = true;
    }
}

