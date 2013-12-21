<?php

/**
 * @file
 * Node API integration.
 */


function _node_expire_node_load(&$ntypes, $nodes, $types) {
  // Only deal with node types that have the Node expire feature enabled
  $ntypes = variable_get('node_expire_ntypes', array());
  $node_expire_enabled = array();

  // Check if node_expire are enabled for each node.
  // If node_expires are not enabled, do nothing.
  foreach ($nodes as $node) {
    // Store whether node_expires are enabled for this node.
    if ((isset($ntypes[$node->type])) and ($ntypes = $ntypes[$node->type])) {
      $node_expire_enabled[] = $node->nid;
    }
  }

  // For nodes with node_expire enabled, fetch information from the database.
  if (!empty($node_expire_enabled)) {
    $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 0);
    $result = db_query('SELECT nid, expire, expired, lastnotify FROM {node_expire} WHERE nid IN (:node_expire_enabled)',
      array(':node_expire_enabled' => $node_expire_enabled));
    foreach ($result as $record) {
      if ($handle_content_expiry == 0) {
          $nodes[$record->nid]->expire = $record->expire;
      } else {
          $nodes[$record->nid]->expire = date(NODE_EXPIRE_FORMAT, $record->expire);
      }
      $nodes[$record->nid]->expired = $record->expired;
      $nodes[$record->nid]->lastnotify = $record->lastnotify;
    }
  }
}

/**
 * Implementation of hook_node_prepare().
 */
function _node_expire_node_prepare(&$ntypes, $node) {
  // To prevent default value 1969-12-31 check also $ntypes['default'].
  if (!isset($node->expire) && $ntypes['default']) {
    $node->expire = format_date(strtotime($ntypes['default']), 'custom', NODE_EXPIRE_FORMAT);
  }
  // This gives a way to users without edit exipration permission to update nodes with default expiration.
  if (isset($node->expire) && !user_access('edit node expire')) {
    $node->expire = format_date(strtotime($ntypes['default']), 'custom', NODE_EXPIRE_FORMAT);
  }
}

/**
 * Implementation of hook_node_validate().
 */
function _node_expire_node_validate(&$ntypes, $node) {
  // The only restriction we have is that the node can't expire in the past.
  if ($node->expire == '') {
    if (!empty($ntypes['required']) && $ntypes['default']) {
      form_set_error('expire_date', t('You must choose an expiration date.'));
    }
  }
  elseif (!$expire = strtotime($node->expire) or $expire <= 0) {
    form_set_error('expire_date', t('You have to specify a valid expiration date.'));
  }
  elseif (variable_get('node_expire_past_date_allowed', 0) == 0 && $expire <= REQUEST_TIME) {
    form_set_error('expire_date', t("You can't expire a node in the past!"));
  }
  elseif (!empty($ntypes['max']) and $expire > strtotime($ntypes['max'], $node->created)) {
    form_set_error('expire_date', t('It must expire before %date.',
    array('%date' => format_date(strtotime($ntypes['max'], $node->created), 'custom', NODE_EXPIRE_FORMAT))));
  }
}

/**
 * Implementation of hook_node_update() and hook_node_insert().
 */
function _node_expire_node_update_insert(&$ntypes, $node) {
  $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 0);
  if ($handle_content_expiry == 0) {
    // Old (legacy) style of processing
    // Has the expiration been removed, or does it exist?
    if (isset($node->expire)) {
      db_delete('node_expire')
        ->condition('nid', $node->nid)
        ->execute();
      // Should we create a new record?
      if ($node->expire) {
        if (strtotime($node->expire)) {
          $node->expire = strtotime($node->expire);
        }
        $node->expired = FALSE;
        drupal_write_record('node_expire', $node);
      }
    }
  } else {
    // Create a proper $node_expire stdClass
    $node_expire = new stdClass();
    $node_expire->nid = $node->nid;

    // Expire
    if (strtotime($node->expire)) {
      $node_expire->expire = strtotime($node->expire);
    } else {
      $node_expire->expire = REQUEST_TIME + 31557600; // Now plus one year
    }

    // Expired
    if (isset($node->expired)) {
      $node_expire->new_record = 0;
      $node_expire->expired = $node->expired;
    } else {
      $node_expire->new_record = 1;
      $node_expire->expired = 0; // Default value
    }

    // Lastnotify
    if (isset($node->lastnotify)) {
      $node_expire->lastnotify = $node->lastnotify;
    } else {
      $node_expire->lastnotify = 0; // Default value
    }

    // Write the record
    if ($node_expire->new_record) {
      drupal_write_record('node_expire', $node_expire);
    } else {
      drupal_write_record('node_expire', $node_expire, 'nid');
    }
  }
}

/**
 * Implementation of hook_node_delete().
 */
function _node_expire_node_delete(&$ntypes, $node) {
  db_delete('node_expire')
    ->condition('nid', $node->nid)
    ->execute();
}

function _node_expire_form_alter_nodeform(&$ntypes, &$form, &$form_state, $form_id) {
  // Check if the Node expire feature is enabled for the node type
  $node = isset($form['#node']) ? $form['#node'] : NULL;

  $node_expire_control_content_type = variable_get('node_expire_control_content_type', 0);
  if ($node_expire_control_content_type == 1) {
    if (!isset($ntypes['enabled']) || !$ntypes['enabled']) return;
  }

  // Convert the timestamp into a human readable date
  if (is_numeric($node->expire)) {
    $node->expire = format_date($node->expire, 'custom', NODE_EXPIRE_FORMAT);
  }
  // This supports node to never expire.
  if (empty($ntypes['default']) && empty($node->expire)) {
    $ntypes['required'] = FALSE;
  }
  if (user_access('edit node expire')) {
    $expire_field = array(
      '#title' => t('Expiration date'),
      '#description' => t('Time date to consider the node expired. Format: %time (YYYY-MM-DD).',
        array('%time' => format_date(REQUEST_TIME, 'custom', NODE_EXPIRE_FORMAT))),
      '#type' => 'textfield',
      '#maxlength' => 25,
      '#required' => $ntypes['required'],
      '#default_value' => $node->expire,
    );
  }
  else {
    $expire_field = array(
      '#type' => 'value',
      '#value' => $node->expire,
    );
  }

  // Put the expire field into 'Publising options' if possible
  if (user_access('administer nodes')) {
    $form['options']['expire'] = &$expire_field;
  }
  else {
    $form['expire'] = &$expire_field;
  }

  if (isset($node->expired)) {
    $form['node_expire'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
}
