const char mainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <style>
        * {
            box-sizing: border-box;
        }

        html {
            font-family: Arial, Helvetica Neue, Helvetica, sans-serif;
        }

        .row {
            display: table;
            width: auto;
            height: auto;
            margin: 0 auto;
        }

        span {
            padding-right: 15px;
        }

        label {
            display: inline-block;
            width: 150px;
            font-size: 14px;
            text-align: right;
            padding: 0 5px;
        }

        input {
            display: inline-block;
            font-size: 14px;
            text-align: left;
            padding: 0 5px;
        }

        input.update {
            font-size: 14px;
            width: 20em;
            height: 2em;
            text-align: center;
        }

        h3 {
            font: 16px arial, sans-serif;
            font-weight: bold;
            border-bottom: 1px solid #737373;
            color: #373737;
        }

        .header {
            background-color: #006600;
            color: #ffffff;
            text-align: center;
            padding: 15px;
        }

        .footer {
            background-color: #006600;
            color: #ffffff;
            text-align: center;
            font-size: 12px;
            padding: 15px;
        }
    </style>
</head>

<body>
    <div class='header'>
        <h2>ASCD - ESP8266 WIFI Setup</h2>
    </div>
    <div id='main'>
        <div class='row'>
            <h3>WIFI Settings</h3>
            <p>
                <label for='lstSSID'>WIFI AP SSID</label>
                <select id='lstSSID' tabindex='1'>
                </select>
            </p>
            <p>
                <label for='txtPassword'>WIFI Password</label>
                <input type='password' id='txtPassword' tabindex='2' size='10'>
                <span id='sPass' style='color: red; display: none;'>Missing Password</span>
            </p>
        </div>
        <div class='row'>
            <h3>ASCD Settings</h3>
            <p>
                <label for='txtServer'>Server Address</label>
                <input type='text' id='txtServer' tabindex='3' size='20' value='submit.vortexit.co.nz'>
                <span id='sServer' style='color: red; display: none;'>Missing Server</span>
            </p>
            <p>
                <label for='txtUserHash'>User Hash</label>
                <input type='text' id='txtUserHash' tabindex='4' size='10'>
                <span id='sHash' style='color: red; display: none;'>Missing User Hash</span>
            </p>
            <p>
                <label for='txtCDUnitID'>CDUnitID</label>
                <input type='number' id='txtCDUnitID' tabindex='5' size='8'>
                <span id='sID' style='color: red; display: none;'>Missing CDUnitID</span>
            </p>
            <p>
                <label for='$lstBAUDRate'>BAUD Rate</label>
                <select id='lstBAUDRate' tabindex='6'>
                    <option value='9600'>9600</option>
                    <option value='14400'>14400</option>
                    <option value='19200'>19200</option>
                    <option value='28800'>28800</option>
                    <option value='38400'>38400</option>
                    <option value='57600'>57600</option>
                    <option selected='selected' value='115200'>115200</option>
                </select>
            </p>
            <br>
            <center>
                <input type='button' class='update' id='btnUpdate' value='Update'>
            </center>
            <br>
            <br>
            <br>
        </div>
    </div>
    <div>
        <br>
        <span id='spanResponse'></span>
        <br>
    </div>
    <div class='footer'>
        <p>Vortex It</p>
    </div>
    <script>
        getData();
        document.getElementById('btnUpdate').onclick = buttonUpdate;
        // if (document.getElementById('lstSSID').options.length == 0) alert('No WIFI AP(s) found!');
        function buttonUpdate() {
            var chkPass = true;
            if (document.getElementById('txtPassword').value == '') {
                document.getElementById('sPass').style.display = 'inline';
                chkPass = false;
            } else {
                document.getElementById('sPass').style.display = 'none';
            }
            if (document.getElementById('txtServer').value == '') {
                document.getElementById('sServer').style.display = 'inline';
                chkPass = false;
            } else {
                document.getElementById('sServer').style.display = 'none';
            }
            if (document.getElementById('txtUserHash').value == '') {
                document.getElementById('sHash').style.display = 'inline';
                chkPass = false;
            } else {
                document.getElementById('sHash').style.display = 'none';
            }
            if (document.getElementById('txtCDUnitID').value == '') {

                document.getElementById('sID').style.display = 'inline';
                chkPass = false;
            } else {
                document.getElementById('sID').style.display = 'none';
            }
            if (chkPass == true) {
                var saveData = 'SSID=' + encodeURIComponent(document.getElementById('lstSSID').value) +
                    '&Pass=' + encodeURIComponent(document.getElementById('txtPassword').value) +
                    '&Server=' + encodeURIComponent(document.getElementById('txtServer').value) +
                    '&UserHash=' + encodeURIComponent(document.getElementById('txtUserHash').value) +
                    '&CDUnitID=' + encodeURIComponent(document.getElementById('txtCDUnitID').value) +
                    '&BAUDRate=' + encodeURIComponent(document.getElementById('lstBAUDRate').value)
                sendData(saveData);
                // alert(saveData);
            }
        }
        function sendData(inData) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    if (this.responseText == 'Successful') {
                        document.getElementById('main').style.display = 'none';
                        document.getElementById('spanResponse').innerHTML = this.responseText;
                    }
                }
            };
            xhttp.open('GET', 'saveSettings?' + inData, true);
            xhttp.send();
        }

        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    if (this.responseText == '') {
                        alert('No WIFI AP(s) found!');
                    } else {
                        var commaSSID = this.responseText;
                        var arraySSID = commaSSID.split(',');
                        // alert(arraySSID);
                        arraySSID.forEach(addListOption);
                        // addListOption(objFaultCodes[key].BatteryFaultType, objFaultCodes[key].BatteryFaultCodeID, 'lstFaultCodes');
                        // alert('SSID: ' + this.responseText);
                    }
                }
            };
            xhttp.open("GET", "getSSID", true);
            xhttp.send();
        }

        function addListOption(item) {
            var element = document.createElement('option');
            element.text = item;
            element.value = item;

            var selectToAppend = document.getElementById('lstSSID');
            selectToAppend.appendChild(element);
        }	
    </script>
</body>

</html>
)=====";