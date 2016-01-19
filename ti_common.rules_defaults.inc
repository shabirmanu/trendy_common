<?php
/**
 * Implements hook_default_rules_configuration
 * 
 * This hook scans the rules directory and loads all *.rule files and then imports all the rules in the system.
 * 
 * @return array An array of rules configurations with the configuration names as keys. 
 * @see http://drupalcontrib.org/api/drupal/contributions!rules!rules.api.php/function/hook_default_rules_configuration/7 hook_default_rules_configuration
 */
function ti_common_default_rules_configuration() {
	$dir = drupal_get_path('module', 'ti_common') . "/rules";
	$rules_files = file_scan_directory($dir, '/.*\.rule$/');
	$rules = array();
	foreach($rules_files as $path => $rule_info) {
		$name = $rule_info->name;
		$import_data = file_get_contents($path);
		$rules[$name] = entity_import('rules_config', $import_data);
	}
	return $rules;
}