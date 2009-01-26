<?php
// $Id$

/**
 * @file
 * Node type integration.
 */

/**
 * Implementation of hook_form_alter().
 */
function _node_expire_form_node_type_form_alter_validate(&$form, &$form_state) {
  $node_expire = &$form_state['values']['node_expire'];
  if (!empty($node_expire) and !strtotime($node_expire)) {
    form_set_error('node_expire', 'This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.');
  }
}


/**
 * Implementation of hook_form_alter().
 */
function _node_expire_form_node_type_form_alter_submit(&$form, &$form_state) {
  $ntypes = variable_get('node_expire_ntypes', array());
  $ntypes[$form_state['values']['type']]  = $form_state['values']['node_expire'];
  variable_set('node_expire_ntypes', $ntypes);
}
