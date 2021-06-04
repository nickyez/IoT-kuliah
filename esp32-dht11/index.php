<html>
    <head>
        <title>Kelompok 5 - TI4B</title>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
        // <script type = "text/JavaScript">
        //     function AutoRefresh(t) {
        //       setTimeout("location.reload(true);", t);
        //     }
        // </script>
        <style>
            .wrapper{
                margin: 0 auto;
                width: 1000px;
            }
        </style>
    </head>
    // onload = "JavaScript:AutoRefresh(3000);"
    <body class="bg-dark">
        <div class="wrapper">
<?php
    echo "<table class='table table-dark table-hover'>";
    echo "<tr><th>Id_Data</th><th>Nama Sensor</th><th>Nilai Suhu</th><th>Nilai Humidity</th><th>waktu</th></tr>";
    class TableRows extends RecursiveIteratorIterator {
        function __construct($it) {
            parent::__construct($it, self::LEAVES_ONLY);
        }
        function current() {
            return "<td style='color:#00ff00;'>" . parent::current(). "</td>";
        }
        function beginChildren() {
            echo "<tr>";
        }
        function endChildren() {
            echo "</tr>" . "\n";
        }
    }
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "kuliah_iot";
    try {
        $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $stmt = $conn->prepare("SELECT id_data, nama_sensor, nilai_temperature, nilai_humidity,waktu FROM tampung_data ORDER BY waktu DESC LIMIT 0,50");
        $stmt->execute();
        // set the resulting array to associative
        $result = $stmt->setFetchMode(PDO::FETCH_ASSOC);
        foreach(new TableRows(new RecursiveArrayIterator($stmt->fetchAll())) as $k=>$v) {
            echo $v;
        }
    } catch(PDOException $e) {
        echo "Error: " . $e->getMessage();
    }
    $conn = null;
    echo "</table>";
?>
</div>
</body>
</html>