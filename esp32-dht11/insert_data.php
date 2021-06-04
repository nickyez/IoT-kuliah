<?php
    $servername = "localhost";
    $username = "root";
    $password = ""; // sesuaikan dengan password phpmyadmin
    $dbname = "kuliah_iot"; 
    try {
        $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
        // set the PDO error mode to exception
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $nama_sensor=htmlspecialchars($_GET["nama_sensor"]) ; // 'sensor_A';
        $temp=htmlspecialchars($_GET["temp"]); //34;
        $humi=htmlspecialchars($_GET["humi"]);
        date_default_timezone_set("Asia/Jakarta");
        $waktu=date("Y-m-d H:i:s");
        $sql = "INSERT INTO tampung_data (id_data,nama_sensor,nilai_temperature,nilai_humidity,waktu) VALUES (NULL,'$nama_sensor','$temp','$humi','$waktu')";
        // use exec() because no results are returned
        $conn->exec($sql);
        echo "New record created successfully";
    } catch(PDOException $e) {
        echo $sql . "<br>" . $e->getMessage();
    }
    $conn = null;
?>
