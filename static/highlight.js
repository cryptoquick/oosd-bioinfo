function init() {
	makeXHR("POST", "diffs", null, highlight);
}

function highlight(diffs) {
	JSON.parse(diffs);
	
}
