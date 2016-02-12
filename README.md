# Commerce RajaOngkir

This module integrates RajaOngkir with [Drupal](//drupal.org) [Commerce](//drupal.org/project/commerce) [Shipping](//drupal.org/project/commerce_shipping).

RajaOngkir is a web service that serves as an abstraction layer for every carrier's shipping rate calculation API from Indonesia.

This means through one service call you can rate a shipment for

- Citra Van Titipan Kilat (TIKI)
- Eka Sari Lorena (ESL)
- Jalur Eka Nugraha (JNE)
- POS Indonesia (POS)
- Priority Cargo and Package (PCP)
- RPX Holding (RPX)

_This module requires an active RajaOngkir.com account in order to obtain estimated shipping rates._

## Requirement

- [Commerce Shipping](//drupal.org/project/commerce_shipping)
- [Commerce Physical](//drupal.org/project/commerce_physical)
- [Address Field ID](//www.drupal.org/sandbox/is/2129777)

## Installation
- Using [drush](https://github.com/drush-ops/drush)
```Shell
cd to/your/drupal/project
drush dl commerce_rajaongkir
drush en commerce_rajaongkir
```
- Manual install [Installing modules (Drupal 7)](https://www.drupal.org/documentation/install/modules-themes/modules-7).

## Configuration
- Enable physical field (dimensions and weight) e.g.
```Shell
admin/commerce/products/types/product/fields
```
- Enable addressfield_id format handlers e.g.
```Shell
admin/commerce/customer-profiles/types/billing/fields/commerce_customer_address
admin/commerce/customer-profiles/types/shipping/fields/commerce_customer_address
```
- Configure this module e.g.
```Shell
admin/commerce/config/shipping/methods/commerce-rajaongkir/edit
```
and provide:
  - API key
  - Account type
  - Shipping services
  - Origin shipping address (administrative and locality)
