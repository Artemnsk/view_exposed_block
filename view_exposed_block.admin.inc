<?php

/**
 * System settings for view_exposed_block module.
 * TODO: better form and validation.
 */
function view_exposed_block_admin_form($form, $form_state) {
	$view_exposed_block_blocks = variable_get('view_exposed_block_blocks', array());
	$i = 0;
	foreach ($view_exposed_block_blocks as $machine_name => $setting) {
		$form['block_' . $i] = _view_exposed_block_admin_form_setting_template($i, $machine_name . ':' . $setting);
		$i++;
	}
	// Empty option for new setting.
	$form['block_' . $i] = _view_exposed_block_admin_form_setting_template($i);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	return $form;
}

/**
 * Returns setting template.
 */
function _view_exposed_block_admin_form_setting_template($number, $default_value = '') {
	return array(
		'#type' => 'textfield',
		'#title' => 'Block ' . $number,
		'#default_value' => $default_value,
		'#description' => 'Format: block_machine_name:view|display|exposed_filter_key',
	);
}

// TODO: at least validation that such block doesn't exist.

/**
 * Submit callback for view_exposed_block_admin_form().
 */
function view_exposed_block_admin_form_submit($form, &$form_state) {
	$view_exposed_block_blocks_new = array();
	$i = 0;
	while (isset($form_state['values']['block_' . $i])) {
		if (!empty($form_state['values']['block_' . $i])) {
			list($block_machine_name, $setting) = explode(':', $form_state['values']['block_' . $i]);
			$view_exposed_block_blocks_new[$block_machine_name] = $setting;
		}
		$i++;
	}
	// Save settings in variable.
	variable_set('view_exposed_block_blocks', $view_exposed_block_blocks_new);
}