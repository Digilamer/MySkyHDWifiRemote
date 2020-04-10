// Copy and paste inside the variable the entire html code
const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
<title>SKY VRA</title>
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="mobile-web-app-capable" content="yes">
<link rel="manifest" href="/manifest.json">
<style>

html, body {
    position:fixed;
    top:0px;
    bottom:0px;
    left:0px;
    right:0px;
}

body {
  font-family:Verdana, Geneva, sans-serif;
  font-size:3vmin; /*14px;*/
  text-align:center;
  font-weight:bold;
  width:100%;
  height:90%;
  background-color:#2d254e;
  }

.wrapper {
    width:95%;
    display:inline-block;
    text-align:center;
    position:absolute;
    top:0px; right:0px; bottom:0px; left:0px;
    border: 2px solid orange;
    /* height:100vh; */
  }

a {
  text-decoration:none;
  color:rgb(237, 243, 255);
  display:block;
}

.footer {
  text-decoration:none;
  color:rgb(128, 128, 128);
  font-size:2.5vmin;
  font-weight:normal;
  text-align:right;
  padding-right:5px;
}

table {
  text-align:center;
    border-collapse: separate;
    border-spacing: 8px;
    padding: 5px;
  margin-left:auto;
  margin-right:auto;
  width:80vw;
  height:12vh;
}

table tr {
  height:4%;
  }
td, th { background: #707070; } 
  thead { background: transparent; }
  
table td {
  padding: 5px;
  width:25%;
  max-width:25%;
  text-align:center;
  overflow:hidden;
  border: 1px #003366;
  border-radius: 5px;
  }
.smTxt {
  font-size:2.5vmin;
  }
</style>

<script>
function lock(orientation) {
  fullScreen();
  screen.orientation.lock(orientation);
}
function fullScreen() {
  // Kind of painful, but this is how it works for now
  if (document.documentElement.requestFullscreen) {
    document.documentElement.requestFullscreen();
  } else if (document.documentElement.mozRequestFullScreen) {
    document.documentElement.mozRequestFullScreen();
  } else if (document.documentElement.webkitRequestFullscreen) {
    document.documentElement.webkitRequestFullscreen();
  } else if (document.documentElement.msRequestFullscreen) {
    document.documentElement.msRequestFullscreen();
  }
}
</script>

</head>

<body onload="lock('portrait')">
<div class='wrapper'>
<table style="height:20%;">
    <tr><td colspan='2'><i><a href='ir?code=SKY'>MySKY Remote</a></i></td><td>&nbsp;</td>  <td><a href='ir?code=PWR'>&#9728;</a></td></tr>
    <tr class='smTxt'><td><a href='ir?code=GUI'>Guida TV</a></td> <td><a href='ir?code=PRI'>Primafila</a></td> <td><a href='ir?code=MNU'>Menu</a></td> <td><a href='ir?code=INT'>Interattivi</a></td></tr>
</table>

<table style="width:80%; height:20%;">
<tr><td><a href='ir?code=INF'>Info</a></td> <td><a href='ir?code=UP'>&uarr;</a></td> <td><a href='ir?code=PU'>P+</a></td></tr>
<tr><td><a href='ir?code=LT'>&larr;</a></td> <td><a href='ir?code=OK'>OK</a></td> <td><a href='ir?code=RT'>&rarr;</a></td></tr>
<tr><td>&nbsp;</td> <td><a href='ir?code=DN'>&darr;</a></td> <td><a href='ir?code=PD'>P-</a></td></tr>
</table>

<table style="width:70%; height:20%;">
<tr><td><a href='ir?code=TXT'>&#8633;</a></td> <td><a href='ir?code=ESC'>ESC</a></td> <td><a href='ir?code=MY'>&#10084;</a></td></tr>
<tr><td><a href='ir?code=REW'>&Lt;</a></td> <td><a href='ir?code=PAU'>||</a></td> <td><a href='ir?code=FFW'>&Gt;</a></td></tr>
<tr><td><a href='ir?code=REC' style="color:rgb(255,0,0)">&reg;</a></td>
<td><a href='ir?code=PLY'>&#10148;</a></td> <td><a href='ir?code=STP'>&#8718;</a></td> </tr>
</table>

<table style="width:50%; height:5%;">
<tr><td style="background-color:rgb(255,0,0)"><a href='ir?code=RED'>&nbsp;</a></td> <td style="background-color:rgb(0,255,0)"><a href='ir?code=GRN'>&nbsp;</a></td> <td style="background-color:rgb(255,255,0)"><a href='ir?code=YLW'>&nbsp;</a></td> <td style="background-color:rgb(0,0,255)"><a href='ir?code=BLU'>&nbsp;</a></td></tr>
</table>
<table style="width:60%; height:20%;">
<tr><td><a href='ir?code=1'>1</a></td> <td><a href='ir?code=2'>2</a></td> <td><a href='ir?code=3'>3</a></td></tr>
<tr><td><a href='ir?code=4'>4</a></td> <td><a href='ir?code=5'>5</a></td> <td><a href='ir?code=6'>6</a></td></tr>
<tr><td><a href='ir?code=7'>7</a></td> <td><a href='ir?code=8'>8</a></td> <td><a href='ir?code=9'>9</a></td></tr>
<tr><td>&nbsp;</td><td><a href='ir?code=0'>0</a></td> <td>&nbsp;</td> </tr>
</table>

<table style="height:10%;">
    <tr class='smTxt'><td><a href='ir?code=EUSP'>Eurosport 1</a></td><td><a href='ir?code=SKY1'>Sky Uno</a></td><td><a href='ir?code=SMGP'>Sky Moto GP</a></td>  <td><a href='ir?code=SARE'>Sky Arena</a></td></tr>
</table>
<p class="footer">&nbsp;<i>V1.0.1</i></p>
</div>
</body>
</html>
)=====";
