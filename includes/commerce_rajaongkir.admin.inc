<?php

/**
 * @file
 * Handles admin settings page for Commerce Ongkir module.
 */

/**
 * Returns commerce_rajaongkir_settings_form().
 */
function commerce_rajaongkir_settings_form($form, &$form_state) {
  module_load_include('inc', 'addressfield_rajaongkir', 'addressfield_rajaongkir.administrative_areas');
  module_load_include('inc', 'addressfield_rajaongkir', 'addressfield_rajaongkir.localities');

  $form = array();
  $administrative_areas = addressfield_rajaongkir_get_administrative_areas();

  if (isset($form_state['values']['commerce_rajaongkir_province'])) {
    $administrative_areas_selected = $form_state['values']['commerce_rajaongkir_province'];
  }
  else {
    $administrative_areas_selected = variable_get('commerce_rajaongkir_province');
  }

  $form['auth'] = array(
    '#title' => t(' Commerce RajaOngkir authentication'),
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
    '#options' => commerce_rajaongkir_account_type_get(),
    '#title' => t('Account type'),
    '#type' => 'select',
  );

  $form['origin'] = array(
    '#prefix' => '<div id="commerce-rajaongkir-origin-wrapper">',
    '#suffix' => '</div>',
    '#title' => t('Origin shipping address'),
    '#type' => 'fieldset',
  );
  $form['origin']['commerce_rajaongkir_province'] = array(
    '#ajax' => array(
      'callback' => 'ajax_commerce_rajaongkir_origin_callback',
      'wrapper' => 'commerce-rajaongkir-origin-wrapper',
    ),
    '#default_value' => variable_get('commerce_rajaongkir_province'),
    '#options' => $administrative_areas,
    '#title' => t('Province'),
    '#type' => 'select',
  );
  $form['origin']['commerce_rajaongkir_city'] = array(
    '#ajax' => array(
      'callback' => 'ajax_commerce_rajaongkir_origin_callback',
      'wrapper' => 'commerce-rajaongkir-origin-wrapper',
    ),
    '#default_value' => variable_get('commerce_rajaongkir_city'),
    '#options' => addressfield_rajaongkir_get_localities($administrative_areas_selected),
    '#title' => t('City'),
    '#type' => 'select',
  );

  $form['services'] = array(
    '#title' => t('Enable shipping services'),
    '#type' => 'fieldset',
  );

  $couriers_get = array();

  foreach (commerce_rajaongkir_services_get() as $key => $value) {
    $couriers_get[$key] = $key;
  }

  $form['services']['commerce_rajaongkir_couriers'] = array(
    '#default_value' => variable_get('commerce_rajaongkir_couriers', array()),
    '#options' => $couriers_get,
    '#type' => 'checkboxes',
  );

  return system_settings_form($form);
}

/**
 * Returns commerce_rajaongkir_account_types_get().
 */
function commerce_rajaongkir_account_type_get() {
  $options = array(
    '' => t('- Select -'),
    'starter' => t('Starter'),
    'basic' => t('Basic'),
    'pro' => t('Pro'),
  );

  return $options;
}

/**
 * Returns ajax_commerce_rajaongkir_origin_callback().
 */
function ajax_commerce_rajaongkir_origin_callback($form, $form_state) {
  return $form['origin'];
}
