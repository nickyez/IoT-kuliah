<?php 
            $koneksi = mysqli_connect(
                'localhost', 
                'root',
                '',
                'kuliah_iot'
            );
            if(isset($_GET['lamp'])){
                $st = $_GET['lamp'];
                $ex = explode("-",$st);
                $status = $ex[0];
                $id_lamp = $ex[1];
                $insert = "UPDATE `status_lampu` SET `status_lampu`='$status' WHERE `id_lampu` = '$id_lamp'"; 
                mysqli_query($koneksi,$insert);
            }
            ?>
<html>
<head>
     <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-+0n0xVW2eSR5OomGNYDnhzAbDsOXxcvSN1TPprVMTNDbiYZCxYbOOl7+AMvyTG2x" crossorigin="anonymous">
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css2?family=Quicksand:wght@600&display=swap" rel="stylesheet">
    <style>
    * {
        font-family: 'Quicksand', sans-serif;
    }

    .mycheckbox input[type="checkbox"] {
        display: none;
    }

    .mycheckbox input[type="checkbox"]+label {
        background: url('img/lamp-off.png') no-repeat;
        width: 200px;
        height: 200px;
    }

    .mycheckbox input[type="checkbox"]:checked+label {
        background: url('img/lamp-on.png') no-repeat;
    }

    .glowing-border {
        border: 2px solid #444;
        border-radius: 7px;
    }

    .glowing-border:hover {
        outline: none;
        border-color: #9ecaed;
        box-shadow: 0 0 10px #9ecaed;
    }
    </style>
</head>
<body>
    <div class="container">
        <div class="row justify-content-center my-2">
            <?php 
            $sql = "SELECT `id_lampu`,`nama_lampu`,`status_lampu` FROM `status_lampu`";
            $query = mysqli_query($koneksi, $sql);
            while($data = mysqli_fetch_row($query)){
                $id_lampu = $data[0];
                $nama_lampu = $data[1];
                $status_lampu = $data[2];
            ?>
                <div class="col-md-5 glowing-border mx-2 p-2" style="width:200px;height:200px">
                    <h4><?php echo $nama_lampu; ?></h4>
                    <form action="index.php" method="get">
                        <div class="mycheckbox mx-4 my-1">
                            <button type="submit" style="background:transparent; border:none; color:transparent;">
                                <input type="checkbox" name="lamp" id="<?php echo $id_lampu; ?>"
                                    value="<?php if($status_lampu=="yes"){ echo "no-$id_lampu";}elseif($status_lampu=="no"){ echo "yes-$id_lampu";} ?>"
                                    <?php if($status_lampu=="yes"){ echo "checked";}else{ echo "";} ?> />
                                <label for="<?php echo $id_lampu; ?>"></label>
                            </button>
                        </div>
                    </form>
                </div>
                <?php } ?>
            </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-gtEjrD/SeCtmISkJkNUaaKMoLD0//ElJ19smozuHV6z3Iehds+3Ulb9Bn9Plx0x4" crossorigin="anonymous">
    </script>
</body>

</html>