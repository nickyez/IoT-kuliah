<?php
$conn = mysqli_connect('localhost', 'root', '', 'kuliah_iot');
mysqli_set_charset($conn, 'utf8');
$query = mysqli_query($conn, 'SELECT * FROM status_lampu');
while($row = mysqli_fetch_assoc($query)) {
$data[] = $row;
}
$json = json_encode($data);
echo $json;
?>