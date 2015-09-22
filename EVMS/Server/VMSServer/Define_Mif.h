#define PATH_LOGIN					L"/login"
#define PATH_USER					L"/user"
#define PATH_ROLE					L"/role"
#define PATH_VMS					L"/vms"
#define PATH_USER_VMS				L"/user/vms"
#define PATH_VMS_PROGRAM			L"/vms/program"
#define PATH_PROGRAM				L"/program"
#define PATH_DEVICE					L"/vmsmodel"
#define PATH_MONITORING				L"/monitoring"
#define PATH_IMAGE					L"/imagesource"
#define PATH_ACTION					L"/action"
#define PATH_HISTORY				L"/history"

#define vms_ok						0		//Thành công
#define not_found_user				400		//Không tồn tại user
#define not_found_program			401		//Không có template
#define not_save_program			402		//Không save được tempalte
#define not_found_history			403		//Không có history
#define user_exist					404		//User đã tồn tại
#define wrong_password				405		//Sai mật khẩu
#define not_found_vms_device		406		//Không tồn tại thiết bị Device
#define template_name_exist			407		//Tên template đã tồn tại
#define template_not_exist			408		//template không tồn tại
#define unknow_url					409     //Request url unkonow
#define not_match_content_type		410     //Default request POST and PUT with content-type: application\json
#define not_match_json_data 		411     //data receive not is json type
#define not_found_parameter_user	412		//Không tồn tại user


#define update_user_failed			450		
#define insert_user_failed			451		
#define delete_user_failed			452	
#define get_list_user_failed		453

#define insert_vms_failed			420
#define exist_vms_name				421
#define exist_vms_ip				422
#define update_vms_failed			423
#define delete_vms_failed			424
#define get_list_vms_failed			425
#define assign_list_vms_failed		426

#define insert_role_failed			431
#define update_role_failed			432
#define delete_role_failed			433
#define get_list_role_failed		434

#define insert_program_failed		440
#define update_program_failed		441
#define delete_program_failed		442
#define get_list_program_failed		443

#define apply_vms_ok				460
#define apply_vms_fail				461


#define get_list_history_failed		500


