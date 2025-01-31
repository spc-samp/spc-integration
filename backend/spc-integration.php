<?php
header('Content-Type: application/json');

$script_dir = dirname(__FILE__);
$base_dir = dirname($script_dir);
$upload_dir = $base_dir . '/exemple_directory/exemple_servers/';

if (!is_dir($base_dir . '/exemple_directory')) {
    $response = [
        'success' => false,
        'message' => 'Server Error: The (exemple_directory) directory does not exist. Please report this issue to the (SPC Team).'
    ];
    echo json_encode($response);

    exit;
}

if (!is_dir($upload_dir)) {
    $response = [
        'success' => false,
        'message' => 'Server Error: (exemple_servers) directory does not exist. Please report this issue to the (SPC Team).'
    ];
    echo json_encode($response);

    exit;
}

if (!is_writable($upload_dir)) {
    $response = [
        'success' => false,
        'message' => 'Server Error: Upload directory is not writable. Please report this issue to the (SPC Team).'
    ];
    echo json_encode($response);

    exit;
}

$api_key = 'YOUR_SECURE_KEY_TO_ACCESS_PHP'; 

function Validate_Request($provided_key) {
    global $api_key;

    return hash_equals($api_key, $provided_key);
}

$raw_data = file_get_contents('php://input');
$post_data = [];
parse_str($raw_data, $post_data);

$action = $_GET['action'] ?? '';
$api_key_provided = $post_data['api_key'] ?? '';
$response = ['success' => false, 'message' => ''];

if (!Validate_Request($api_key_provided)) {
    $response = [
        'success' => false,
        'message' => 'Authentication Error: Invalid API key provided. Please check your configuration.'
    ];
    echo json_encode($response);

    exit;
}

function Process_Image_URL($image_URL, $is_encoded) {
    if ($is_encoded) {
        $decoded = base64_decode($image_URL);

        if ($decoded === false)
            return false;

        return $decoded;
    }

    return $image_URL;
}

function Process_Web_URL($web_URL, $is_encoded) {
    if ($is_encoded) {
        $decoded = base64_decode($web_URL);

        if ($decoded === false)
            return false;

        return $decoded;
    }

    return $web_URL;
}

switch ($action) {
    case 'create':
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $server_ip = $post_data['server_ip'] ?? '';
            $server_port = $post_data['server_port'] ?? '';
            $image_URL = $post_data['image_url'] ?? '';
            $web_URL = $post_data['web_url'] ?? '';
            $is_encoded = isset($post_data['encoded']) && $post_data['encoded'] === 'true';
            
            if (empty($server_ip) || empty($server_port)) {
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Server IP and Port are required parameters.'
                ];

                break;
            }
            
            $filename = preg_replace('/[^a-zA-Z0-9\-\.]/', '', $server_ip . '-' . $server_port . '.json');
            $file_path = $upload_dir . $filename;
            
            if (file_exists($file_path)) {
                $response = [
                    'success' => false,
                    'message' => 'File error: The data for this server already exists. The "update" action was used to update the data.'
                ];

                break;
            }
            
            $processed_image_URL = Process_Image_URL($image_URL, $is_encoded);
            $processed_web_URL = Process_Web_URL($web_URL, $is_encoded);

            if ($processed_image_URL === false) {
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Invalid image URL encoding provided.'
                ];

                break;
            }

            if ($processed_web_URL === false) {
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Invalid web URL encoding provided.'
                ];

                break;
            }
            
            $json_data = json_encode([
                'spc_integration_image' => $processed_image_URL,
                'spc_web_url' => $processed_web_URL
            ], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);
            
            if (file_put_contents($file_path, $json_data) !== false) {
                chmod($file_path, 0644);
                $response = [
                    'success' => true,
                    'message' => 'Server data successfully created for ' . $server_ip . ':' . $server_port
                ];
            }
            else {
                $response = [
                    'success' => false,
                    'message' => 'Server error: Failed to create server data file. Please report this issue to the (SPC Team).'
                ];
            }
        }
        else {
            $response = [
                'success' => false,
                'message' => 'Method Error: This endpoint only accepts POST requests.'
            ];
        }

        break;
        
    case 'update':
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $server_ip = $post_data['server_ip'] ?? '';
            $server_port = $post_data['server_port'] ?? '';
            $image_URL = $post_data['image_url'] ?? '';
            $web_URL = $post_data['web_url'] ?? '';
            $is_encoded = isset($post_data['encoded']) && $post_data['encoded'] === 'true';
            
            if (empty($server_ip) || empty($server_port)) {
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Server IP and Port are required parameters.'
                ];

                break;
            }
            
            $filename = preg_replace('/[^a-zA-Z0-9\-\.]/', '', $server_ip . '-' . $server_port . '.json');
            $file_path = $upload_dir . $filename;
            
            if (!file_exists($file_path)) {
                $response = [
                    'success' => false,
                    'message' => 'File error: Server data not found. The "create" action was used to create a new server record.'
                ];

                break;
            }
            
            $old_content = file_get_contents($file_path);
            $backup_path = $file_path . '.bak';

            if (file_put_contents($backup_path, $old_content) === false) {
                $response = [
                    'success' => false,
                    'message' => 'Server Error: Failed to create backup before update.'
                ];

                break;
            }
            
            $processed_image_URL = Process_Image_URL($image_URL, $is_encoded);
            $processed_web_URL = Process_Web_URL($web_URL, $is_encoded);

            if ($processed_image_URL === false) {
                unlink($backup_path);
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Invalid image URL encoding provided.'
                ];

                break;
            }

            if ($processed_web_URL === false) {
                unlink($backup_path);
                $response = [
                    'success' => false,
                    'message' => 'Validation Error: Invalid web URL encoding provided.'
                ];

                break;
            }
            
            $json_data = json_encode([
                'spc_integration_image' => $processed_image_URL,
                'spc_web_url' => $processed_web_URL
            ], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);
            
            if (file_put_contents($file_path, $json_data) !== false) {
                $response = [
                    'success' => true,
                    'message' => 'Server data successfully updated to ' . $server_ip . ':' . $server_port
                ];
                unlink($backup_path);
            }
            else {
                file_put_contents($file_path, $old_content);
                unlink($backup_path);
                $response = [
                    'success' => false,
                    'message' => 'Server error: Failed to update server data, original data restored. Please report this issue to the (SPC Team).'
                ];
            }
        }
        else {
            $response = [
                'success' => false,
                'message' => 'Method Error: This endpoint only accepts POST requests.'
            ];
        }

        break;
        
    default:
        $response = [
            'success' => false,
            'message' => 'Route Error: Invalid action. Supported actions are "create" and "update".'
        ];
}

echo json_encode($response);