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
    if (isset($_POST['id'])) {
        $id = intval($_POST['id']);
        $sql = "SELECT data FROM my_table WHERE id = $id";
        $result = $conn->query($sql);
    
        if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            echo json_encode(array("id" => $id, "data" => $row['data']));
        } else {
            echo json_encode(array("error" => "Không tìm thấy dữ liệu với ID này"));
        }
    } else {
        echo json_encode(array("error" => "Thiếu tham số ID"));
    }
    $conn->close();
}
?>
