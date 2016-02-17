<?php

/**
 * @file
 * Handles admin settings page for Commerce RajaOngkir module.
 */

/**
 * Form callback.
 *
 * Settings form used to collect RajaOngkir API credentials and enable supported
 * shipping couriers.
 *
 * @param $form
 *   Drupal form API.
 * @param $form_state
 *   Form state.
 * @return
 *   Admin settings form.
 */
function commerce_rajaongkir_settings_form($form, &$form_state) {
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block');

  $option_account_types = array_change_key_case(commerce_rajaongkir_account_type());
  $option_couriers = array_keys(commerce_rajaongkir_service());

  if (isset($form_state['values']['commerce_rajaongkir_administrative_area'])) {
    $administrative_area_selected = $form_state['values']['commerce_rajaongkir_administrative_area'];
  }
  else {
    $administrative_area_selected = variable_get('commerce_rajaongkir_administrative_area');
  }

  if (isset($form_state['values']['commerce_rajaongkir_locality'])) {
    $locality_selected = $form_state['values']['commerce_rajaongkir_locality'];
  }
  else {
    $locality_selected = variable_get('commerce_rajaongkir_locality');
  }

  $form = array();

  $form['auth'] = array(
    '#title' => t('Authentication'),
    '#type' => 'fieldset',
  );
  $form['auth']['commerce_rajaongkir_api_key'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_api_key'),
    '#description' => t('Your RajaOngkir API key.'),
    '#title' => t('API key'),
    '#type' => 'textfield',
  );
  $form['auth']['commerce_rajaongkir_account_type'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_account_type'),
    '#empty_value' => '',
    '#options' => $option_account_types,
    '#title' => t('Account type'),
    '#type' => 'select',
  );

  $form['rate'] = array(
    '#title' => t('Rate request settings'),
    '#type' => 'fieldset',
  );
  $form['rate']['commerce_rajaongkir_rates_timeout'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_rates_timeout', 60),
    '#description' => t('Default to 60 seconds. Set to 0 during testing to avoid caching failed rate request responses.'),
    '#field_suffix' => t('seconds'),
    '#title' => t('Cached rates timeout'),
    '#type' => 'textfield',
  );

  $form['courier'] = array(
    '#title' => t('Available shipping couriers'),
    '#type' => 'fieldset',
  );
  $form['courier']['commerce_rajaongkir_courier'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_courier', array()),
    '#empty_value' => '',
    '#options' => drupal_map_assoc($option_couriers),
    '#title' => t('Shipping couriers'),
    '#type' => 'checkboxes',
  );

  $form['origin'] = array(
    '#prefix' => '<div id="commerce-rajaongkir-origin-wrapper">',
    '#suffix' => '</div>',
    '#title' => t('Origin shipping address'),
    '#type' => 'fieldset',
  );
  $form['origin']['commerce_rajaongkir_administrative_area'] = array(
    '#ajax' => array(
      'callback' => 'commerce_rajaongkir_origin_ajax_callback',
      'wrapper' => 'commerce-rajaongkir-origin-wrapper',
    ),
    '#default_value' => variable_get('commerce_rajaongkir_administrative_area'),
    '#empty_value' => '',
    '#options' => addressfield_id_administrative_area(),
    '#title' => t('Province'),
    '#type' => 'select',
  );
  $form['origin']['commerce_rajaongkir_locality'] = array(
    '#ajax' => array(
      'callback' => 'commerce_rajaongkir_origin_ajax_callback',
      'wrapper' => 'commerce-rajaongkir-origin-wrapper',
    ),
    '#default_value' => variable_get('commerce_rajaongkir_locality'),
    '#empty_value' => '',
    '#options' => addressfield_id_locality($administrative_area_selected),
    '#title' => t('City/regency'),
    '#type' => 'select',
  );
  $form['origin']['commerce_rajaongkir_dependent_locality'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_dependent_locality'),
    '#empty_value' => '',
    '#options' => addressfield_id_dependent_locality($locality_selected),
    '#title' => t('District/Kecamatan'),
    '#type' => 'select',
  );

  return system_settings_form($form);
}

/**
 * Option list of account type.
 *
 * @return
 *   Account type.
 */
function commerce_rajaongkir_account_type() {
  $account_types = drupal_map_assoc(array(
    t('Starter'),
    t('Basic'),
    t('Pro'),
  ));

  return $account_types;
}

/**
 * AJAX callback for commerce_rajaongkir_origin.
 *
 * @param $form
 *   Form
 * @param $form_state
 *   Form_state.
 * @return
 *   Form origin.
 */
function commerce_rajaongkir_origin_ajax_callback($form, $form_state) {
  return $form['origin'];
}
