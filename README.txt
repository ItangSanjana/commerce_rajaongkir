
           N
           ohN
        my:/sshdN
     mo. `/ssssssyhN
   m/``-+ssssssssssshN
  mo/+ssssssssssssssshN
 NysssssssssssssssssyyhN
 mssssssssosssssssyyyyym
 msssss:`   `:+syyo-`.sm
  ysss:        :/`    s
  Nysso.   .:++++s+``+N
    mhyyyyysysyyyoyym
      Ndhhys++++ohm
          NNNNN

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Maintainers

INTRODUCTION
------------

This module integrates RajaOngkir with Drupal Commerce Shipping
https://drupal.org/project/commerce_shipping.

RajaOngkir is a web service that serves as an abstraction layer for every
carrier's shipping rate calculation API from Indonesia.

This means through one service call you can rate a shipment for

 * Citra Van Titipan Kilat (TIKI)
 * Eka Sari Lorena (ESL)
 * Jalur Eka Nugraha (JNE)
 * POS Indonesia (POS)
 * Priority Cargo and Package (PCP)
 * RPX Holding (RPX)

This module requires an active RajaOngkir account in order to obtain estimated
shipping rates.

 * To submit bug reports and feature suggestions, or to track changes:
   https://www.drupal.org/project/issues/addressfield_id

REQUIREMENTS
------------

 * Commerce Shipping https://drupal.org/project/commerce_shipping
 * Commerce Physical https://drupal.org/project/commerce_physical
 * Address Field Indonesia https://www.drupal.org/project/addressfield_id

INSTALLATION
------------

 * Using Drush https://github.com/drush-ops/drush
   cd to/your/drupal/project
   drush dl commerce_rajaongkir
   drush en commerce_rajaongkir

 * or manual install see:
   https://www.drupal.org/documentation/install/modules-themes/modules-7

CONFIGURATION
-------------

 * Enable physical field (dimensions and weight) e.g.
   admin/commerce/products/types/product/fields

 * Enable addressfield_id format handlers e.g.
   admin/commerce/customer-profiles/types/billing/fields/commerce_customer_address
   admin/commerce/customer-profiles/types/shipping/fields/commerce_customer_address

 * Configure this module e.g.
   admin/commerce/config/shipping/methods/commerce-rajaongkir/edit

MAINTAINERS
-----------

Current maintainers:
 * Itang Sanjana (ItangSanjana) - https://www.drupal.org/user/1193514
