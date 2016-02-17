<?php

/**
 * @file
 * Search query extender and helper functions.
 */

/**
 * @param $province_id
 *   Province ID.
 * @return
 *   List of province.
 */
function commerce_rajaongkir_restful_province($province_id = NULL) {
  $endpoint = 'province';
  $params['id'] = isset($province_id) ? $province_id : array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * @param $city_id
 *   City ID.
 * @param $province_id
 *   Province ID.
 * @return
 *   List of city.
 */
function commerce_rajaongkir_restful_city($city_id = NULL, $province_id = NULL) {
  $endpoint = 'city';
  $params['id'] = isset($city_id) ? $city_id : array();
  $params['province'] = isset($province_id) ? $province_id : array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * @param $city_id
 *   City ID.
 * @param $subdistrict_id
 *   Subdistrict ID.
 * @return
 *   List of subdistrict.
 */
function commerce_rajaongkir_restful_subdistrict($city_id = NULL, $subdistrict_id = NULL) {
  $endpoint = 'subdistrict';
  $params['city'] = isset($city_id) ? $city_id : array();
  $params['id'] = isset($subdistrict_id) ? $subdistrict_id : array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * @param $origin
 *   Origin shipping address.
 * @param $origintype
 *   Origin shipping address trype.
 * @param $destination
 *   Shipping destination address.
 * @param $destinationtype
 *   Shipping destination address type.
 * @param $weight
 *   Shipping weight.
 * @param $courier
 *   Shipping courier.
 * @param $length
 *   Product length.
 * @param $width
 *   Product width.
 * @param $height
 *   Product height.
 * @param $diameter
 *   Product diameter.
 * @return
 *   Shiping cost/rates result.
 */
function commerce_rajaongkir_restful_cost($origin, $origintype, $destination, $destinationtype, $weight, $courier, $length, $width, $height, $diameter) {
  $endpoint = 'cost';
  $params = array(
    'origin' => $origin,
    'originType' => $origintype,
    'destination' => $destination,
    'destinationType' => $destinationtype,
    'weight' => $weight,
    'courier' => $courier,
    'length' => $length,
    'width' => $width,
    'height' => $height,
    'diameter' => $diameter,
  );
  $rest_client = commerce_rajaongkir_restful_post($endpoint, $params);

  return $rest_client;
}

/**
 * For international shipping.
 *
 * @param $city_id
 *   City ID.
 * @param $province_id
 *   Province ID.
 * @return
 *   List of origin city.
 */
function commerce_rajaongkir_restful_internationalorigin($city_id = NULL, $province_id = NULL) {
  $endpoint = 'internationalOrigin';
  $params['id'] = isset($city_id) ? $city_id : array();
  $params['province'] = isset($province_id) ? $province_id : array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns list of available country.
 *
 * @param $country_id
 *   country ID.
 * @return
 *   List of destination country.
 */
function commerce_rajaongkir_restful_internationaldestination($country_id = NULL) {
  $endpoint = 'internationalDestination';
  $params['id'] = isset($country_id) ? $country_id : array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * @param $origin
 *   Origin shipping address.
 * @param $destination
 *   Shipping destination address.
 * @param $weight
 *   Shipping weight.
 * @param $courier
 *   Shipping courier.
 * @param $length
 *   Product length.
 * @param $width
 *   Product width.
 * @param $height
 *   Product height.
 * @return
 *   Shiping cost/rates result.
 */
function commerce_rajaongkir_restful_internationalcost($origin, $destination, $weight, $courier, $length, $width, $height) {
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
  $rest_client = commerce_rajaongkir_restful_post($endpoint, $params);

  return $rest_client;
}

/**
 * Returns currency converter.
 */
function commerce_rajaongkir_restful_currency() {
  $endpoint = 'currency';
  $params = array();
  $rest_client = commerce_rajaongkir_restful_get($endpoint, $params);

  return $rest_client;
}

/**
 * Returns shipping tracking.
 *
 * @param $waybill_number
 *   Waybill number.
 * @param $courier
 *   Courier.
 * @return
 *   Shiping waybill/tracking information.
 */
function commerce_rajaongkir_restful_waybill($waybill_number, $courier) {
  $endpoint = 'waybill';
  $params = array(
    'waybill' => $waybill_number,
    'courier' => $courier,
  );
  $rest_client = commerce_rajaongkir_restful_post($endpoint, $params);

  return $rest_client;
}

/**
 * CURL post.
 *
 * @param $endpoint
 *   Endpoint.
 * @param $params
 *   Params.
 * @return
 *   CURL post results.
 */
function commerce_rajaongkir_restful_post($endpoint, $params) {
  $account_type = variable_get('commerce_rajaongkir_account_type', array());
  $query = drupal_http_build_query($params);

  if ($account_type == 'pro') {
    $url = 'http://' . $account_type . '.rajaongkir.com/api/' . $endpoint;
  }
  elseif ($account_type == 'starter' || $account_type == 'basic') {
    $url = 'http://rajaongkir.com/api/' . $account_type . '/' . $endpoint;
  }
  else {
    $url = NULL;
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
* CURL get.
*
* @param $endpoint
*   Endpoint.
* @param $params
*   Params.
* @return
*   CURL get results.
*/
function commerce_rajaongkir_restful_get($endpoint, $params) {
  $account_type = variable_get('commerce_rajaongkir_account_type', array());
  $query = drupal_http_build_query($params);

  if ($account_type == 'pro') {
    $url = 'http://' . $account_type . '.rajaongkir.com/api/' . $endpoint . '?' . $query;
  }
  elseif ($account_type == 'starter' || $account_type == 'basic') {
    $url = 'http://rajaongkir.com/api/' . $account_type . '/' . $endpoint . '?' . $query;
  }
  else {
    $url = NULL;
  }

  $options = array(
    'headers' => array(
      'key' => variable_get('commerce_rajaongkir_api_key'),
    ),
  );

  $request = drupal_http_request($url, $options);

  return $request;
}
