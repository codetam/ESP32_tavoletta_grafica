<?php
session_start();

require('vendor/autoload.php');

use \PhpMqtt\Client\MqttClient;
use \PhpMqtt\Client\ConnectionSettings;

/* Solo se l'utente è loggato e ha cliccato sul button Carica... */
if (isset($_SESSION['uid']) && isset($_POST['image']) && isset($_POST['submit'])) {
    $uid = $_SESSION['uid'];
    $imageId = $_POST['image'];
    $clientId = 3;
    $server = 'iot.dayngine.com';
    $port = 1883;
    $username = 'gtab_user';
    $password = 'SX54NipFEVZjwm';
    $clean_session = true;
    $mqtt_version = MqttClient::MQTT_3_1_1;

    $connectionSettings = (new ConnectionSettings)
        ->setUsername($username)
        ->setPassword($password)
        ->setKeepAliveInterval(60)
        ->setLastWillTopic('gtab/' . $uid . '/last-will')
        ->setLastWillMessage('client disconnect')
        ->setLastWillQualityOfService(2);

    $mqtt = new MqttClient($server, $port, $clientId, $mqtt_version);

    $mqtt->connect($connectionSettings, $clean_session);
    $mqtt->publish('gtab/' . $uid, $imageId, 0, true);
    header("location: additional_pages/success.php");
    exit();
} 
else {
    header("location: additional_pages/error.php");
    exit();
}