function init() {
	makeXHR("POST", "diffs", null, highlight);
}

var diffarr;
var last = 0;
var elA;
var elB;
var oldA = "";
var oldB = "";
var newA = "";
var newB = "";
var offset = 0;
var line = 0;
var spot = 0;

function highlight(diffs) {
	// Goes through each character in the string and highlights individually.
	// Simple and low performance, but easiest to get working properly.
	diffarr = JSON.parse(diffs);
	elA = document.getElementById('align0');
	elB = document.getElementById('align1');
	oldA = elA.innerText;
	oldB = elB.innerText;
	
	for (var i = 0, ii = oldA.length; i < ii; i++) {
		if (diffarr[spot] == i) {
			newA += '<span class="hred">' + oldA.charAt(i) + '</span>';
			newB += '<span class="hred">' + oldB.charAt(i) + '</span>';
			spot++;
		}
		else {
			newA += oldA.charAt(i);
			newB += oldB.charAt(i);
		}
	}
	
	// Replace the text.
	elA.innerHTML = newA;
	elB.innerHTML = newB;
}
