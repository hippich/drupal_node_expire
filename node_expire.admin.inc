<?php

/**
 * @file
 * Administration page callbacks for the node_expire module.
 *
 */

/**
 * Administrative settings.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function node_expire_admin_settings() {
  $form['handle_content_expiry'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Handle content cxpiry'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['handle_content_expiry']['node_expire_handle_content_expiry'] = array(
    '#type'          => 'radios',
    '#title'         => t('Handle content expiry'),
    '#default_value' => variable_get('node_expire_handle_content_expiry', 0),
    '#options'       => array(
      0 => t('In legacy mode'),
      1 => t('Trigger "Content Expired" event every cron run when the node is expired'),
      2 => t('Trigger "Content Expired" event only once when the node is expired'),
    ),
    '#description'   => t('"Only once" option allows to ignore nodes, which already have been processed.') . '<br />' .
    t('Legacy mode means: not possible to allow expiry separately for each particular node type, trigger "Content Expired" event every cron run, legacy data saving'),
  );

  $form['date_defaults'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Date defaults'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['date_defaults']['node_expire_common_default_date'] = array(
    '#title' => t('Common default expiration date'),
    '#description' => t('Default expiration date - if one is not set up for particular node type.') . ' ' .
      t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.')  . ' ' .
      t('Has no effect in legacy mode'),
    '#type' => 'textfield',
    '#default_value' => variable_get('node_expire_common_default_date', NODE_EXPIRE_COMMON_DEFAULT_DATE),
  );

  $form['past_date_allowed'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Expire date in the past'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['past_date_allowed']['node_expire_past_date_allowed'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Allow expire date in the past'),
    '#default_value' => variable_get('node_expire_past_date_allowed', 0),
    '#description'   => t('Checking this box will allow to save nodes with expire date in the past. This is helpful during site development and testing.'),
  );

  return system_settings_form($form);
}  //  End of node_expire_admin_settings().

