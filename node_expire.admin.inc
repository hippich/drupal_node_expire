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
  $form['control_content_type'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Allow node expiry options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['control_content_type']['node_expire_control_content_type'] = array(
    '#type'          => 'radios',
    '#title'         => t('Allow node expiry'),
    '#default_value' => variable_get('node_expire_control_content_type', 0),
    '#options'       => array(0 => t('For all node types (classic)'), 1 => t('Separately for each particular node type')),
    '#description'   => t('This option controls how the expire functionality is assigned to different node types.'),
  );

  $form['trigger_only_once'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Trigger "Content Expired" rule'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['trigger_only_once']['node_expire_trigger_only_once'] = array(
    '#type'          => 'radios',
    '#title'         => t('Trigger "Content Expired" rule for particular node'),
    '#default_value' => variable_get('node_expire_trigger_only_once', 0),
    '#options'       => array(0 => t('Every cron run (classic)'), 1 => t('Only once')),
    '#description'   => t('"Only once" option allows to ignore nodes, which already have been processed.'),
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

