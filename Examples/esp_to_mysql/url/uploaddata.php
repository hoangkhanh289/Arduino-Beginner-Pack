<?php 
$hostname = "localhost";
$username = "root";
$password = "";
$database = "my_database";

$conn = mysqli_connect($hostname, $username, $password, $database);
if (!$conn) {
    die("Connection Failed: " . mysqli_connect_error());
}
echo "Database connection is OK<br>";


if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = intval($_POST['id']);
    $data = mysqli_real_escape_string($conn, $_POST['data']); 
    $sql = "UPDATE my_table SET data='$data' WHERE id='$id'"; 
    if (mysqli_query($conn, $sql)) {
        echo "Record updated successfully";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
}
$conn->close(); 
?>
