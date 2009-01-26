<?php
// $Id$

/**
 * @file
 * Rules module integration.
 */

/**
 * Implementation of hook_rules_action_info().
 * @ingroup rules
 */
function node_expire_rules_action_info() {
  return array(
    'node_expire_set_expired' => array(
      'arguments' => array(
        'node'      => array('type' => 'node', 'label' => t('content expired')),
      ),
      'label'     => t('Unset the expired flag'),
      'module'    => 'Node',
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 * @ingroup rules
 */
function node_expire_rules_condition_info() {
  return array(
    'node_expire_rules_expired_check' => array(
      'arguments' => array(
        'node'      => array('type' => 'node', 'label' => t('Content')),
      ),
      'label'     => t('Content is expired'),
      'help'      => 'Evaluates to TRUE, if the given content has one of the selected content types.',
      'module'    => 'Node',
    ),
  );
}

/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
function node_expire_rules_event_info() {
  return array(
    'node_expired' => array(
      'arguments' => rules_events_node_arguments(t('content expired'), t("content's author")),
      'label'     => t('Content expired'),
      'module'    => 'Node',
    ),
  );
}

/**
 * Check if the node has the the "Expired" flag on.
 *
 * @param $node
 *   Object. The Node object.
 */
function node_expire_rules_expired_check($node) {
  return (!empty($node->expire) and $node->expire <= time());
}

/**
 * Set the "Expired" flag on nodes after they are called by Rules module
 * or prevent it from happening.
 *
 * @param $nids
 *   Object or Array. The Node object or a array list with all node IDs
 *   that shuold be changed the expired flag to TRUE.
 * @param $set
 *   Boolean (optional). Only TRUE if its time to set the nodes list as expired.
 */
function node_expire_set_expired($nids, $set = FALSE) {
  static $nid_no = array();
  if (empty($close)) {
    $nid_no[] = $node->nid;
  }
  else {
    if ($nids = array_diff($nids, $nid_no)) {
      db_query('UPDATE {node_expire} SET expired = 1
        WHERE nid IN ('. implode(',', $nids) .')');
    }
  }
}
