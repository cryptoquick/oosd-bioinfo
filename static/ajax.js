function makeXHR (type, operation, data, callback) {
	var newData;
	var status = -1;
	var request = new XMLHttpRequest();
	if (!request) {
		loggit("Unable to connect.");
	}
	
	request.open(type, operation, true);
	request.setRequestHeader("Content-type", "application/json");
	// console.log(type + ", directory: /" + operation + ", data: " + data);
	
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			newData = request.responseText;
			callback(newData);
		}
	}
	
	try {
		request.send(data);
	} catch (e) {
		console.log(e);
	}
}


