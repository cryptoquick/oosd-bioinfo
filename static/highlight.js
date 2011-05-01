function init() {
	makeXHR("POST", "diffs", null, highlight);
}

function highlight(diffs) {
	var diffarr = JSON.parse(diffs);
	var last = 0;
	var elA = document.getElementById('align0');
	var elB = document.getElementById('align1');
	var oldA = elA.innerText;
	var oldB = elB.innerText;
	var newA = "";
	var newB = "";
	
	for (var i = 0, ii = diffarr.length; i < ii; i++) {
		var strA = oldA.substring(last+1, diffarr[i]);
		var chrA = oldA.charAt(diffarr[i]);
		var strB = oldB.substring(last+1, diffarr[i]);
		var chrB = oldB.charAt(diffarr[i]);
		
		newA += strA + '<span class="hred">' + chrA + '</span>';
		newB += strB + '<span class="hred">' + chrB + '</span>';
		
		last = diffarr[i];
	}
	// Get the last bit.
	newA += oldA.substring(last+1, oldA.length);
	newB += oldB.substring(last+1, oldB.length);
	
	/* For formatting break-lines into strings...
	lenA = newA.length;
	spot = 0;
	formA = "";
	// Format to 80 characters wide.
	while(lenA > 80) {
		formA += newA.substr(spot, 80 + spot);
		formA += '<br>';
		spot += 80;
		lenA -= 80;
	}
	
	// Get the last bit.
	formA += newA.substr(spot, lenA - spot);
	*/
	// Replace the text.
	elA.innerHTML = newA;
	elB.innerHTML = newB;
}
