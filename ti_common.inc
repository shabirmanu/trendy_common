<?php

/**
 *  Callback function gets the trendy indie proposed roles for designer
 * 
 * @return array Array of designer role lables
 */
function _ti_common_get_designer_roles(){
  return $roles = array(
    'Starving Artist',
    'Craftsperson',
    'Artisan',
    'Dilettante',
    'Virtuoso'
  );
}


/**
 * The callback returns an array of roles distinguishing designer and non designer roles
 * 
 * @return array An array of designer roles as (rid => rid) and non designer roles as (rid => 0)
 */
function _ti_common_get_designer_field_roles(){
  $system_roles = user_roles();
	$blocked_roles = array_diff($system_roles, _ti_common_get_designer_roles());
  $allowed_roles = array_intersect($system_roles, _ti_common_get_designer_roles());
  $field_roles = array();

  foreach($allowed_roles as $rid => $role) {
    $field_roles[$rid] = $rid;
  }

  foreach($blocked_roles as $rid => $role) {
    $field_roles[$rid] = 0;
  }

  return $field_roles;
}

/**
 * Callback function to check if the provided user is designer and for which role he was subscribed
 * 
 * @param stdClass $user Drupal user object
 * 
 * @return mixed An array containing one element and role id as key and role title as value or FALSE
 */
function _ti_common_user_is_desiger($user) {
  $active_roles =  array_intersect(_ti_common_get_designer_roles(), $user->roles);
  $roles = array();
  foreach($active_roles as $role_name) {
    $role = user_role_load_by_name($role_name);
    $roles[$role->rid] = $role;
  }

  if (!empty($roles)) {
    return $roles;
  } else {
    return FALSE;
  }
}