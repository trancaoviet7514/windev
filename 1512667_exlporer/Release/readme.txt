Họ Tên: Trần Cao Việt
MSSV: 1512667

* Các chức năng làm được:
  Tạo ra TreeView bên trái, ListView bên phải. 
	
	*Xét TreeView:
		+ Tạo node root là This PC
		+ Lấy danh sách các ổ đĩa trong máy bằng hàm GetLogicalDrives hoặc GetLogicalDriveStrings, thêm các ổ đĩa vào node root.
		+ Bắt sự kiện Expanding, duyệt nội dung thư mục bằng FindFirstFile & FindNextFile.
	
	*Xét ListView:
		+ Hiển thị toàn bộ thư mục và tập tin tương ứng với một đường dẫn.
		+ Bấm đôi vào một thư mục sẽ thấy toàn bộ thư mục con và tập tin.
		+ Tạo ra ListView có 4 cột: Tên, Loại, Thời gian chỉnh sửa, Dung lượng. Với thư mục có 2 cột Tên và Loại. Với tập tin có 4 cột: Tên, Thời gian chỉnh sửa, Dung lượng, loại tập tin.
		+ Sử dụng icon hệ thống.
		+ Bấm đôi vào file thì hệ thống tự động chạy ứng dụng tương ứng.


* Luồng sự kiện chính: Chạy chương trình lên, hiển thị node This PC trên TreeView bên trái ở trạng thái collapse (thu gọn). Bấm vào sẽ xổ xuống các node con là danh sách ổ đĩa. Bên phải là Listview nhấp đôi vào thư mục sẽ hiện ra các item con của foler đó, còn nếu là file thì khởi động chương trình tương ứng lên.

* Luồng sự kiện phụ: không có.

Link bitbucket:https://trancaoviet7514@bitbucket.org/trancaoviet7514/windev.git
Link youtube:https://youtu.be/GNH2-ZqQZFM
