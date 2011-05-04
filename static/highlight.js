function init() {
//	makeXHR("POST", "diffs", null, highlight);
}

function highlight(diffs) {
	var diffarr = JSON.parse(diffs);
	var breakarr = diffarr; // For a linebreak-adjusted array.
	var last = 0;
	var elA = document.getElementById('align0');
	var elB = document.getElementById('align1');
	var oldA = elA.innerText;
	var oldB = elB.innerText;
	var newA = "";
	var newB = "";
	var offset = 0;
	var line = 0;

// diffarr = 	[14, 89, 100, 145, 222, 232, 245, 253, 279, 352]
// breakarr =	[70, 125, 180, 405, 470, 520, 265, 305, 435, 480];
// 				[18, 93, 104, 149, 226, 236, 249, 257, 283, 356]

/*	for (var i = 0, ii = diffarr.length; i < ii; i++) {
	//	var linemod = diffarr[i] % 80;
		if (diffarr[i] > 80) {
			breakarr.push(diffarr[i] + 4); // For <br>
		}
	}*/
	console.log(breakarr);
	for (var i = 0, ii = breakarr.length; i < ii; i++) {
		if (Math.floor(breakarr[i] / 80) > line) {
			offset += 4; // For <br>
		//	last += 4;
			line++;
		}
		
		var strA = oldA.substring(last + 1, breakarr[i] + offset);
		var chrA = oldA.charAt(breakarr[i]);
		var strB = oldB.substring(last + 1, breakarr[i] + offset);
		var chrB = oldB.charAt(breakarr[i]);
		console.log(breakarr[i]);
		newA += strA + '<span class="hred">' + chrA + '</span>';
		newB += strB + '<span class="hred">' + chrB + '</span>';
		offset += 19 + 7; // For span tags length
		last = breakarr[i] + 26;
	}
	console.log(offset);
	console.log(line);
	console.log(oldA.length)
	console.log(newA.length)
	// Get the last bit.
	newA += oldA.substring(last+1, oldA.length);
	newB += oldB.substring(last+1, oldB.length);
	
	/* For formatting break-lines into strings...
	nevermind, it's done in python in one line. :)
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
