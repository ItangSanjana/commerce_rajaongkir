<?php

/**
 * @file
 * Search query extender and helper functions.
 */

/**
 * Returns province().
 */
function commerce_rajaongkir_rest_province($province_id = NULL) {
  $endpoint = 'province';
  $params['id'] = (isset($province_id)) ? $province_id : array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns city().
 */
function commerce_rajaongkir_rest_city($city_id = NULL, $province_id = NULL) {
  $endpoint = 'city';
  $params['id'] = (isset($city_id)) ? $city_id : array();
  $params['province'] = (isset($province_id)) ? $province_id : array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns subdistrict().
 */
function commerce_rajaongkir_rest_subdistrict($city_id = NULL, $subdistrict_id = NULL) {
  $endpoint = 'subdistrict';
  $params['city'] = (isset($city_id)) ? $city_id : array();
  $params['id'] = (isset($subdistrict_id)) ? $subdistrict_id : array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns cost().
 */
function commerce_rajaongkir_rest_cost($origin, $originType, $destination, $destinationType, $weight, $courier, $length, $width, $height, $diameter) {
  $endpoint = 'cost';
  $params = array(
    'origin' => $origin,
    'originType' => $originType,
    'destination' => $destination,
    'destinationType' => $destinationType,
    'weight' => $weight,
    'courier' => $courier,
    'length' => $length,
    'width' => $width,
    'height' => $height,
    'diameter' => $diameter,
  );
  $rest_client = commerce_rajaongkir_rest_post($endpoint, $params);

  return $rest_client;
}

/**
 * Returns internationalorigin().
 */
function commerce_rajaongkir_rest_internationalorigin($city_id = NULL, $province_id = NULL) {
  $endpoint = 'internationalOrigin';
  $params['id'] = (isset($city_id)) ? $city_id : array();
  $params['province'] = (isset($province_id)) ? $province_id : array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns internationaldestination().
 */
function commerce_rajaongkir_rest_internationaldestination($country_id = NULL) {
  $endpoint = 'internationalDestination';
  $params['id'] = (isset($country_id)) ? $country_id : array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns internationalcost().
 */
function commerce_rajaongkir_rest_internationalcost($origin, $destination, $weight, $courier, $length, $width, $height) {
  $endpoint = 'internationalCost';
  $params = array(
    'origin' => $origin,
    'destination' => $destination,
    'weight' => $weight,
    'courier' => $courier,
    'length' => $length,
    'width' => $width,
    'height' => $height,
  );
  $rest_client = commerce_rajaongkir_rest_post($endpoint, $params);

  return $rest_client;
}

/**
 * Returns currency().
 */
function commerce_rajaongkir_rest_currency() {
  $endpoint = 'currency';
  $params = array();
  $rest_client = commerce_rajaongkir_rest_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns waybill().
 */
function commerce_rajaongkir_rest_waybill($waybill_number, $courier) {
  $endpoint = 'waybill';
  $params = array(
    'waybill' => $waybill_number,
    'courier' => $courier,
  );
  $rest_client = commerce_rajaongkir_rest_post($endpoint, $params);

  return $rest_client;
}

/**
 * Returns post().
 */
function commerce_rajaongkir_rest_post($endpoint, $params) {
  $query = drupal_http_build_query($params);
  if (variable_get('commerce_rajaongkir_account_type') == 'pro') {
    $url = 'http://' . variable_get('commerce_rajaongkir_account_type') . '.rajaongkir.com/api/' . $endpoint;
  } else {
    $url = 'http://rajaongkir.com/api/' . variable_get('commerce_rajaongkir_account_type') . '/' . $endpoint;
  }
  $options = array(
    'method' => 'POST',
    'data' => $query,
    'headers' => array(
      'Content-Type' => 'application/x-www-form-urlencoded',
      'key' => variable_get('commerce_rajaongkir_api_key'),
    ),
  );
  $request = drupal_http_request($url, $options);

  return $request;
}

/**
 * Returns get().
 */
function commerce_rajaongkir_rest_get($endpoint, $params) {
  $query = drupal_http_build_query($params);
  if (variable_get('commerce_rajaongkir_account_type') == 'pro') {
    $url = 'http://' . variable_get('commerce_rajaongkir_account_type') . '.rajaongkir.com/api/' . $endpoint . '?' . $query;
  } else {
    $url = 'http://rajaongkir.com/api/' . variable_get('commerce_rajaongkir_account_type') . '/' . $endpoint . '?' . $query;
  }
  $options = array(
    'headers' => array(
      'key' => variable_get('commerce_rajaongkir_api_key'),
    ),
  );
  $request = drupal_http_request($url, $options);

  return $request;
}
