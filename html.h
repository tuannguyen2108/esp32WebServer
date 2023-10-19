
const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>ESP32 Web Server</title>
  <link rel="icon" type="image/png" href="https://scontent.fdad3-5.fna.fbcdn.net/v/t1.15752-9/387536720_334757075714076_6984793589882457434_n.png?_nc_cat=109&ccb=1-7&_nc_sid=ae9488&_nc_ohc=KYlLlURSEKIAX8INOol&_nc_oc=AQkSppkZeE2ivx-7ZYgP7DamwGK_f7TUboUlw6h2OClWsmCasWvsI0ibBRkGojJLpBouqk8QwZFzRwJ3ox_d7uQO&_nc_ht=scontent.fdad3-5.fna&oh=03_AdSil6OF4QiXy34ZCEkX3X3hUF_mXkbvLbw-LlP1jO1_Kg&oe=654C8448" />
  <link
    rel="stylesheet"
    href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css"
    integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"
    crossorigin="anonymous"
  />
  <link
    rel="stylesheet"
    href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.2/css/all.min.css"
    integrity="sha512-z3gLpd7yknf1YoNbCzqRKc4qyor8gaKU1qmn+CShxbuBusANI9QpRohGBreCFkKxLhei6S9CQXFEbbKuqLg0DA=="
    crossorigin="anonymous"
    referrerpolicy="no-referrer"
  />
  <style>
    * {
      margin: 0;
      padding: 0;
      overflow-y: none;
      font-family: Arial, Helvetica, sans-serif;
    }
    *:focus {
      outline: 0 !important;
    }
    body{
      /* background-image: url(https://scontent.fdad3-1.fna.fbcdn.net/v/t1.15752-9/387525369_287389397578891_1405844716795295495_n.png?_nc_cat=108&ccb=1-7&_nc_sid=ae9488&_nc_ohc=MF6eF4gbWLoAX9KwhI4&_nc_ht=scontent.fdad3-1.fna&oh=03_AdQ98k4S580TQ55ciKK7koWjjbkrOqF7bEJC1heecIk4Zg&oe=654C7EBE); */
      /* background-repeat: no-repeat;
      background-size: cover; */
      background-color: #e2d9d9ab;
      position: relative;
    }
    ul{
      margin-bottom: 0;
    }
    #header {
      min-height: 130px;
      display: flex; 
      /* justify-content: space-between; */
      align-items: center;
      /* background-color: #009578; */
      background: linear-gradient(to right,rgb(65, 88, 114),rgb(14, 192, 216));
      /* background: transparent; */
      
      position: fixed;
      top: 0;
      left: 0;
      right: 0;
      z-index: 999;
    }
    .header_wp {
      flex-grow: 1;
      color: #fff;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    
    #nav {
      font-size: 18px;
      font-weight: bold;
    }
    .menu {
      display: flex;
      list-style: none;
      margin-right: 50px;
      align-items: center;
      justify-content: center;
      margin-bottom: 0px;
    }

    .menu li {
      padding-left: 30px;
    }
    .menu li a {
      color: #fff;
      text-decoration: none;
    }
    .menu li a:hover {
      /* color: #c9caca; */
    }

    #content {
      margin-top: 190px;
    }
    .content_wp {
    }
    .DHT11 li{
      width: 250px;
      height: 350px;
    }
    .humidity,
    .temprature {
      width: 250px;
    }
    .title_temperature{
      font-size: 24px; 
      /* background-image:  rgb(5, 243, 17); */
      /* -webkit-background-clip: text;
      background-clip: text;
      color: transparent;  */
      font-size: 35px;
      font-weight: 800;
    }
    .title_humidity{
      font-size: 24px; 
      /* background-image:  linear-gradient(to right,#80D0C7 ,#0023e9 );
      -webkit-background-clip: text;
      background-clip: text;
      color: transparent;  */
      font-size: 35px;
      font-weight: 800;
    }
    .gauge {
      width: 100%;
      /* max-width: 250px; */
      font-family: "Roboto", sans-serif;
      font-size: 32px;
      color: #004033;
      /* border: solid 2px #009578; */
      /* border-radius: 50px; */
      background-color: #b91818;
      padding: 20px;
      background: transparent;
    }
    .gauge__border{
      border: solid 2px #fff;
      border-image-source: linear-gradient(to right, rgb(75, 108, 183), rgb(24, 40, 72));
      border-image-slice: 1; 
      border-image-width: 2px; 
      border-image-outset: 0; 
      border-image-repeat: stretch; 
      /* border-radius: 50px; */
      background-color: #fff;

    }

    .gauge__body {
      width: 100%;
      height: 0;
      padding-bottom: 50%;
      background: #b4c0be;
      position: relative;
      border-top-left-radius: 100% 200%;
      border-top-right-radius: 100% 200%;
      overflow: hidden;
    }

    .gauge__fill {
      position: absolute;
      top: 100%;
      left: 0;
      width: inherit;
      height: 100%;
      background: linear-gradient(to left, rgb(255, 255, 255), rgb(7, 161, 233)); 
      transform-origin: center top;
      transform: rotate(0.25turn);
      transition: transform 0.2s ease-out;
    }

    .gauge__cover {
      width: 75%;
      height: 150%;
      background: #ffffff !important;
      border-radius: 50%;
      position: absolute;
      top: 25%;
      left: 50%;
      transform: translateX(-50%);

      /* Text */
      display: flex;
      align-items: center;
      justify-content: center;
      padding-bottom: 25%;
      box-sizing: border-box;
    }
    .frame {
      padding: 20px;
      border-radius: 50px;
      background-color: rgb(217, 214, 214);
    }

    .wp_button .toggleButton {
      /* width: 250px; */
      /* padding: 25px 55px; */
      /* border-radius: 50px; */
      border: none;
      background-color: #fff !important;
      color: #fff;
      font-size: 32px;
    }
    .wp_button button:focus {
      border: none;
    }

    .toggle button:hover {
      background-color: #0cd3ab;
    }
    .toggle i {
      font-size: 130px;
      /* color: #009578; */
      /* background: -moz-linear-gradient(top, #e72c83 0%, #a742c6 100%);
      background: -webkit-linear-gradient(top, #e72c83 0%, #a742c6 100%);
      background: linear-gradient(to bottom, #e72c83 0%, #a742c6 100%); */
      
      /* background: linear-gradient(to left,rgb(5, 243, 17),rgb(248, 224, 3)); */
      /* background: linear-gradient(to left,rgb(5, 243, 17),rgb(248, 224, 3),rgb(228, 6, 6)); */
      background: linear-gradient(to right,rgb(90, 117, 180),rgb(24, 40, 72));
      -webkit-background-clip: text;
      -moz-background-clip: text;
      background-clip: text;
  -webkit-text-fill-color: transparent;
    }

    /*  TOAST MESSAGE */
    
body{
  margin: 0;
}
#wrapper{
  margin: 0;
  display: flex;
  flex-direction: column;
  justify-content: center; 
  align-items: center; 
  height: 100vh; 
  background-color: rgb(240, 240, 240);

}
.hidden{
  display: none !important;
}

#wp-toast{
  display: flex ;
  flex-direction: column;
  justify-content: space-around;
  position: fixed;
  top: 150px;
  right: 32px;
}
.toast{
  background-color: rgb(255, 255, 255);
  display: flex;
  align-items: center;
  margin-bottom: 20px;
  box-sizing: border-box;
  min-width: 400px;
  max-width: 400px;
  border-radius: 3px;
  animation: slideInleft ease 3s, fadeOut linear 2s 3s forwards;
  transition: all linear 3s;
}
@keyframes slideInleft{
  from{
      opacity: 0;
      transform: translateX(calc(100% + 32px));
  }to{
      opacity: 1;
      transform: translateX(0px);
  }
}

/* @keyframes fadeOut{
  to{
      opacity: 0;
  }
} */
.toast-success{
  border-left: solid 5px limegreen ;
  /* display: none; */

}

.toast-info{
  border-left: solid 5px blue ;
}

.toast-warning{
  border-left: solid 5px darkorange ;

}

.toast-error{
  border-left: solid 5px red ;

}

.toast .icon, .toast .close{
  padding: 30px 20px;
  font-size: 25px;
}

.toast .close:hover{
  color: gray;
}
.toast .message{
  
  flex-grow: 1;
}
.toast .message h3{
  margin: 0;
}

.toast .message p{
  margin: 0;
  color: #333;
}

/* button */

.wrapper-btn{
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
}

.btn{
  padding: 20px 30px;
  margin-right: 20px;
  border-radius: 30px;
  min-width: 150px;
  text-align: center;
  font-size: 20px;
  font-weight: 500;
}

.btn:hover{
  color: #fff;
}

.btn-success{
  background-color: rgb(0, 252, 34);
}

.btn-danger{
  background-color: rgba(255, 0, 0, 0.858);
}

       /* large devives (desktops,  less than 1200px) */
       @media(max-width:1199.89px){
          
      }
          /* medium devives (desktops, less than  992px) */
       @media(max-width:991.98px){
        
      }
          /* small devives (desktops, less than  768px) */
       @media(max-width:767.98px){
        .DHT11{
          justify-content: center !important;
        }
        .logo{
          font-size: 30px !important;
        }
        .DHT11 img{
          height: 150px;
        }
        .title_temperature {
          font-size: 25px;
        }

      }
          /* extral small devives (desktops,  less than 576 px) */
       @media(max-width:575.98px){
        .DHT11{
          justify-content: center;
        }
      }

  </style>
</head>
<body>
  <div id="header">
    <div class="header_wp">
      <div>
        <a class="d-flex justify-content-center align-items-center ml-5" style="color: #fff; text-decoration: none;" href=""><img src="https://scontent.fdad3-1.fna.fbcdn.net/v/t1.15752-9/370308314_990794495550701_7957361561041976838_n.png?_nc_cat=110&ccb=1-7&_nc_sid=ae9488&_nc_ohc=QBMy7tMPk_UAX-cQ7b2&_nc_ht=scontent.fdad3-1.fna&oh=03_AdS1833EWHEoXdy-4gEM6FUiDh-8bSQB5lQL5TOj8ZysvQ&oe=654C319B" alt="ESP32 WEBSERVER" style="width: 100px; height: auto;">
          <h1 class="ml-2 logo" style="font-size: 55px; font-weight: 800;">ESP32 WEB SERVER</h1></a>
      </div>
      <div id="nav">
        <ul class="menu">
          <!-- <li>
            <a href=""><i class="fa-solid fa-house"></i> HOME</a>
          </li> -->
          <li>
            <a href=""><i class="fa-solid fa-gear" style="font-size: 40px;"></i></a>
          </li>
        </ul>
      </div>
    </div>
  </div>
  <div id="content">
    <div class="content_wp container">
      <ul class="DHT11 row " style="list-style: none;    justify-content: space-between;">
        <li class="gauge__border humidity col-md-5 d-flex justify-content-center align-items-center mb-3">
          <div class="gauge">
            <div class="gauge__body">
              <div class="gauge__fill"></div>
              <div class="gauge__cover">
                <span id="Humidity"></span>
                <sup class="units">&percnt;</sup>
              </div>
            </div>
            <h2 class="text-center mt-4 title_humidity text-dark">
              Humidity <i class="fa-solid fa-droplet"></i>
            </h2>
          </div>
        </li>
        <li class="temprature gauge__border col-md-5 d-flex justify-content-center align-items-center mb-3">
          <div class="gauge gauge_T">
            <div class="gauge__body gauge__body_T">
              <div class="gauge__fill gauge__fill_T"></div>

              <div class="gauge__cover gauge__cover_T">
                <span id="Temperature"></span>
                <sup class="units">&deg;C</sup>
              </div>
            </div>
            <h2 class="text-center mt-4 title_temperature text-dark">
              Temperature <i class="fa-solid fa-temperature-high"></i>
            </h2>
          </div>
        </li>
      </ul>
      <ul class="DHT11 row " style="list-style: none; justify-content: space-between;">
        <li class="gauge__border gauge wp_button col-md-5 d-flex justify-content-center align-items-center toggle mt-3" id="wp_Buzzer" style="width: 250px;">
          <div class=" gauge d-flex justify-content-center align-items-center flex-column" style="width: 100%; height: auto; ">
              <img style="width: auto; max-height: 250px;" src="https://scontent.xx.fbcdn.net/v/t1.15752-9/280398406_613043649745001_5950239848040211478_n.png?stp=dst-png_p403x403&_nc_cat=104&ccb=1-7&_nc_sid=aee45a&_nc_ohc=fhC6U-4PZ8IAX9O5kDS&_nc_ad=z-m&_nc_cid=0&_nc_ht=scontent.xx&cb_e2o_trans=q&oh=03_AdSoEoMOYMQ-y0hDodVGD45xcTfLSYp0sTS1wVy0MD4B6Q&oe=654CC5A7" alt="BUZZER">
              <div><h3 class="text-dark" style="margin-top: 20px; margin-bottom: 0px; font-weight: 800; text-align: center;">BUZZER IS <span id="Buzzer"></span></h3></div>
          </div>
        </li>
        <li class="gauge__border gauge wp_button col-md-5 d-flex justify-content-center align-items-center toggle mt-3" id="wp_Pump" style="width: 250px;">
          <div class=" gauge d-flex justify-content-center align-items-center flex-column" style="width: 100%; height: auto;">
              <img style="width: auto; max-height: 250px;" src="https://instagram.fdad3-1.fna.fbcdn.net/v/t1.15752-9/387594761_808645377671766_1373420897236850265_n.png?stp=dst-png_p403x403&_nc_cat=103&ccb=1-7&_nc_sid=aee45a&_nc_ohc=cZ9EXTWW4dEAX9IokYZ&_nc_ht=instagram.fdad3-1.fna&oh=03_AdS_HAwQSsXXG8mDyZoJzXnKdkAl1l54GnRzNXCRaqQo2A&oe=654CF679" alt="PUMP">
              <div><h3 class="text-dark" style="margin-top: 20px; margin-bottom: 0px; font-weight: 800; text-align: center;">PUMP IS <span id="Pump"></span></h3></div>
          </div>
        </li>
      </ul>
      <ul class="DHT11 row " style="list-style: none; justify-content: space-between;">
        <li class="gauge__border wp_button col-md-5 d-flex justify-content-center align-items-center toggle mt-3" style="width: 250px;">
          <div class="gauge d-flex justify-content-center align-items-center flex-column" style="width: 100%;padding: 0px ; height: auto;">
              <button class="toggleButton" onclick="getdata('toggleD1')">
                <p class="text-dark font-weight-bold">LED 1</p>
                <i class="fa-solid fa-toggle-off mt-5 mb-5"></i>
                <h2 class="text-dark font-weight-bold">OFF</h2>
              </button>
          </div>
        </li>
        <li class="gauge__border gauge wp_button col-md-5 d-flex justify-content-center align-items-center toggle mt-3" style="width: 250px;">
          <div class=" gauge d-flex justify-content-center align-items-center flex-column" style="width: 100%; height: auto; padding: 0px;">
              <button class="toggleButton" onclick="getdata('toggleD2')">
                <p class="text-dark font-weight-bold">LED 2</p>
                <i class="fa-solid fa-toggle-off mt-5 mb-5"></i>
                <h2 class="text-dark font-weight-bold ">OFF</h2>
              </button>
          </div>
        </li>
      </ul>
  <div id="footer" style="min-height: 250px;"></div>
  <div id="wp-toast">
      
  </div>
  <script>
    //-----------Tạo đối tượng request----------------
    var jsonTem;
    var jsonHum;
    function create_obj() {
      td = navigator.appName;
      if (td == "Microsoft Internet Explorer") {
        obj = new ActiveXObject("Microsoft.XMLHTTP");
      } else {
        obj = new XMLHttpRequest();
      }
      return obj;
    }
    var xhttp = create_obj();

    function getstatusDHT() {
      xhttp.open("GET", "/dataDHT", true);
      xhttp.onreadystatechange = process_json;
      xhttp.send();
    }
    function getdata(url){
        xhttp.open("GET","/"+url,true);
        xhttp.onreadystatechange = process;//nhận reponse 
        xhttp.send();
      }
      //-----------Kiểm tra response--------------------
      function process(){
        if(xhttp.readyState == 4 && xhttp.status == 200){
          //------Updat data sử dụng javascript----------
          ketqua = xhttp.responseText; 
      // console.log(ketqua);

          // document.getElementById("reponsetext").innerHTML=ketqua;       
        }
      }
    //-----------Kiểm tra response-------------------------------
    function process_json() {
      if (xhttp.readyState == 4 && xhttp.status == 200) {
        //------Update data sử dụng javascript-------------------
        var statusDHT_JSON = xhttp.responseText;
        // console.log(statusDHT_JSON);

        var Obj = JSON.parse(statusDHT_JSON);
        // console.log(Obj);
        // console.log(typeof Obj.Temperature);
        jsonTem = parseFloat(Obj.Temperature);
        setGaugeValueT(gaugeElementT, jsonTem / 100);
        jsonHum = parseFloat(Obj.Humidity);
        setGaugeValue(gaugeElementH, jsonHum / 100);
        // console.log(typeof jsonHum);
        document.getElementById("Temperature").innerHTML = Obj.Temperature;
        document.getElementById("Humidity").innerHTML = Obj.Humidity;
        document.getElementById("Pump").innerHTML = Obj.Pump;
        document.getElementById("Buzzer").innerHTML = Obj.Buzzer;
      }
    }
    //---Ham update duu lieu tu dong---
    setInterval(function () {
      getstatusDHT();
    }, 100);
    const gaugeElementH = document.querySelector(".gauge");
    const dataHumidity = document.getElementById("Humidity");
    const titleHumidity = document.querySelector(".title_humidity");
    var Humidity = parseFloat(dataHumidity.textContent);
    function setGaugeValue(gauge, value) {
      if (value < 0 || value > 1) {
        return;
      }

      gauge.querySelector(".gauge__fill").style.transform = `rotate(${
        value / 2
      }turn)`;
      // gauge.querySelector(".gauge__cover").textContent = `${Math.round(
      //   value * 100
      // )}%`;
    }

    const gaugeElementT = document.querySelector(".gauge_T");
    const gaugeFillElementT = document.querySelector(".gauge__fill_T");
    const titleTemperature = document.querySelector(".title_temperature");

    // const dataTemperature = document.getElementById("Temperature");
    // var temperature = dataTemperature.textContent;
    // console.log(temperature);
    function setGaugeValueT(gauge, value) {
      if (value < 0 || value > 0.5) {
        return;
      }

      gauge.querySelector(".gauge__fill_T").style.transform = `rotate(${
        value
      }turn)`;
      if(value > 0.35) {
        document.getElementById("wp_Buzzer").style.background = "#fc5353";
        document.getElementById("wp_Pump").style.background = "#68d7eb";
      }else{
        document.getElementById("wp_Buzzer").style.background = "";
        document.getElementById("wp_Pump").style.background = "";
      }
      if(value <= 0.167){
        gaugeFillElementT.style.background = "rgb(5, 243, 17)";
        titleTemperature.style.backgroundImage  = "rgb(5, 243, 17)";
      }else if(value > 0.167 && value <= 0.33){
        gaugeFillElementT.style.background = "linear-gradient(to left,rgb(5, 243, 17),rgb(248, 224, 3))";
        // titleTemperature.style.backgroundImage  = "linear-gradient(to right,rgb(5, 243, 17),rgb(248, 224, 3))";
      }else{
        gaugeFillElementT.style.background = "linear-gradient(to left,rgb(5, 243, 17),rgb(248, 224, 3),rgb(228, 6, 6))";
        // titleTemperature.style.backgroundImage  = "linear-gradient(to right,rgb(5, 243, 17),rgb(248, 224, 3),rgb(228, 6, 6))";
        // temperatureWarning();

      }
    }
    // setGaugeValue(gaugeElementH, 1);
    // setGaugeValueT(gaugeElementT, 0.4)

    const toggleButton = document.getElementsByClassName("toggleButton");
    let isLightOn = false;
    const buttonArray = Array.from(toggleButton);

    buttonArray.map((button, index) => {
      const icon = button.querySelector("i");
      const status = button.querySelector("h2");
      // console.log(icon);
      button.addEventListener("click", function () {
        if (status.textContent == "OFF") {
          // console.log("on");
          icon.classList.replace("fa-toggle-off", "fa-toggle-on");
          status.textContent = "ON";
        } else {
          // console.log("off");
          icon.classList.replace("fa-toggle-on", "fa-toggle-off");
          status.textContent = "OFF";
        }
        isLightOn = !isLightOn;
      });
    });


// //WARNING MESSAGE
//   // const btnSuccess = document.querySelector(".btn-success");
//   // const btnDanger = document.querySelector(".btn-danger");
//   function toast({ title, message_high, type, icon, iconColor, duration }) {
//   const main = document.getElementById("wp-toast");
//   if (main) {
//   const toast = document.createElement("div");
//   toast.classList.add("toast", `toast-${type}`);
//   toast.innerHTML = `<div class="icon" style = "color: ${iconColor}">
//               ${icon}
//           </div>
//           <div class="message">
//           <h3>${title}</h3>
//           <p>${message_high}</p>
//           </div>
//           <div class="close">
//           <i class="fa-solid fa-circle-xmark"></i>
//           </div>`;
//   main.appendChild(toast);
//   setTimeout(function () {
//     main.removeChild(toast);
//   }, 16000);
//   toast.onclick = function (e) {
//     if (e.target.closest(".close")) {
//       setTimeout(function () {
//         main.removeChild(toast);
//       });
//     }
//   };
// }
// }

// function temperatureWarning() {
// toast({
//   title: "warning",
//   message_high: "The temperature is too high",
//   message_low: "The temperature is too low",
//   type: "warning",
//   icon: ' <i class="fa-sharp fa-solid fa-triangle-exclamation"></i>',
//   iconColor: "red",
//   duration: 3000,
// });
// console.log("warned")
// };
// function humidityWarning() {
// toast({
//   title: "warning",
//   message_high: "The humidity is too high",
//   message_low: "The humidity is too low",
//   type: "warning",
//   icon: '<i class="fa-sharp fa-solid fa-triangle-exclamation"></i>',
//   iconColor: "red",
//   duration: 3000,
// });
// };
  </script>
</body>
</html>




)=====";

