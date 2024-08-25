function changeColor() {
    let red = Math.floor(Math.random() * 255);
    let green = Math.floor(Math.random() * 255);
    let blue = Math.floor(Math.random() * 255);

    document.getElementById("header").style.color = `rgb(${red}, ${green}, ${blue})`;
}