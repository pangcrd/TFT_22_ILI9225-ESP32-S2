
const char MAIN_page[] = R"====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SIÊU CẤP VJP PRO</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f4f4f9;
            color: #333;
        }
         button {
            background-color: #007bff; 
            border: none;
            color: white;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 10px;
            cursor: pointer;
            border-radius: 5px;
            transition: background-color 0.3s, transform 0.2s;
        }

        button:hover {
            background-color: #0056b3; /* Màu nền khi hover */
        }

        button:active {
            background-color: #003d7a; /* Màu nền khi nhấn */
            transform: scale(0.98); /* Hiệu ứng nhấn */
        }
        h1 {
            color: #ff7b7b;
        }
        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }
        .card {
            background-color: #fff;
            padding: 20px;
            margin: 10px;
            border-radius: 10px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1);
            max-width: 300px;
            width: 100%;
        }
        .slider {
            width: 100%;
            height: 8px;
            background: #ddd;
            border-radius: 5px;
            border: 1px solid #ccc;
            outline: none;
            padding: 0;
            margin-top: 10px;
        }
        @media (max-width: 600px) {
            .container {
                padding: 10px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>BẢNG ĐIỀU KHIỂN</h1>
        <div class="card">
            <h3>Điện áp: <span id="voltage">0</span> V</h3>
            <h3>Dòng điện: <span id="current">0</span> A</h3>
            <h3>Công suất: <span id="power">0</span> W</h3>
            <h3>Tiêu thụ: <span id="energy">0</span> kWh</h3>
            <h3>Tần số: <span id="frequency">0</span> Hz</h3>
        </div>
        <div class="card">
            <h3>Nhiệt độ: <span id="temperature">0</span> °C</h3>
            <h3>Độ ẩm: <span id="humidity">0</span> %</h3>
        </div>
        <div class="button">
            <button onclick="toggleFan()">Fan man/auto</button>
            <input type="range" id="fanSpeed" min="0" max="255" class="slider" oninput="setSpeed(this.value)" disabled>
        </div>
        <div class="button">
            <button onclick="resetEnergy()">Reset Energy</button>
        </div>
    </div>

    <script>
        var socket = new WebSocket(`ws://192.168.0.101:81/ws`);

        socket.onmessage = function(event) {
            var data = JSON.parse(event.data);
            document.getElementById('voltage').innerText = data.voltage;
            document.getElementById('current').innerText = data.current;
            document.getElementById('power').innerText = data.power;
            document.getElementById('energy').innerText = data.energy;
            document.getElementById('frequency').innerText = data.frequency;
            document.getElementById('temperature').innerText = data.temperature;
            document.getElementById('humidity').innerText = data.humidity;

            var message = JSON.parse(event.data);
                if (message === "FAN ON") {
                    document.getElementById('button').innerText = "ON";
                } else if (message === "FAN OFF") {
                    document.getElementById('button').innerText = "OFF";
                } else if (message === "slider:enable") {
                    document.getElementById('fanSpeed').disabled = false;
                } else if (message === "slider:disable") {
                    document.getElementById('fanSpeed').disabled = true;
      }
        };


        document.getElementById('resetEnergy').addEventListener('click', function() {
            console.log("Reset Energy button clicked");
            socket.send(JSON.stringify({ action: 'resetEnergy' }));
        });

            function toggleFan() {
            webSocket.send('toggleFan');
            }

            function setSpeed(value) {
            webSocket.send('fanSpeed:' + value);
            }
        socket.onerror = function(error) {
            console.error("WebSocket error:", error);
        };

        socket.onclose = function(event) {
            console.log("WebSocket connection closed");
        };
    </script>
</body>
</html>
)====";
